#include "ChessLib\chess-library\include\chess.hpp"
#include "Lumina.h"
#include "Evaluation/Eval.h"
#include "Helper/SEE.h"
#include "Helper/HelperFunctions.h"
#include "TT/TT.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

#define SEARCH_CANCELLED 0

#define Infinity     9999999
#define Ninfinity   -Infinity

#define UPPERBOUND 1
#define EXACT      2
#define LOWERBOUND 3

#define QSEARCHDEPTH 0
#define StartingPly  0
#define ReduceDepth  2

#define ImmediateMateScore -999999
#define CheckmateThreshold 900000

void Timer(int Milliseconds, std::atomic<bool>& CanSearch) {
    std::this_thread::sleep_for(std::chrono::milliseconds(Milliseconds));
    CanSearch = false;
}

void Lumina::Think(chess::Board& board, int Milliseconds) {
    // Launch Timer thread
    CanSearch = true;
    auto TimerThread = std::thread(Timer, Milliseconds, std::ref(CanSearch));

    CounterTable.Clear();

    chess::Move BestMove     = chess::Move::NO_MOVE;
    int         BestEval     = Ninfinity;
    int         LastBestEval = Ninfinity;

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, board.halfMoveClock(), chess::Move::NO_MOVE);
    std::vector<int> MoveScores;

    // TODO: TUNE THE WINDOW SIZE
    int window = 200;
    int alpha  = Ninfinity;
    int beta   = Infinity;

    for (int PlyRemaining=2;;) {    
        BestEval = Ninfinity;
        MoveScores.clear();
        MoveScores.reserve(LegalMoves.size());

        for (const auto& move : LegalMoves) {
            board.makeMove(move);

            int eval = -Search(board, StartingPly, PlyRemaining, -beta, -alpha, 0, chess::Move::NO_MOVE);

            board.unmakeMove(move);

            if (!CanSearch) {
                break;
            }

            if (eval > BestEval) {
                BestEval = eval;
                BestMove = move;
            }

            MoveScores.push_back(eval);
        }
        
        if (!CanSearch) {
            break;
        }
        
        // Aspiration Windows
        if (BestEval <= alpha || BestEval >= beta){
            alpha = Ninfinity;
            beta  = Infinity;
            continue;
        }
        
        LastBestEval = BestEval;
        alpha = BestEval - window;
        beta  = BestEval + window;
        PlyRemaining++;

        LegalMoves = OrderFromIteration(LegalMoves, MoveScores);

    }

    if (TimerThread.joinable()) {
        TimerThread.join();
    }

    std::cout << "info score cp " << LastBestEval << std::endl;
    std::cout << "bestmove " << chess::uci::moveToUci(BestMove) << std::endl;
}

int Lumina::Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions, const chess::Move& LastMove) {
    if (!CanSearch || board.isRepetition(1)) { return SEARCH_CANCELLED; }
    
    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.hash();
    TTEntry ttEntry;

    int ttype = UPPERBOUND;

    if (TranspositionTable.retrieveTTEntry(key, ttEntry, PlyRemaining)) {
        int NodeType  = ttEntry.nodeType;
        int NodeValue = ttEntry.value;

        if      (NodeType == UPPERBOUND && NodeValue <= alpha) { return NodeValue; }
        else if (NodeType == EXACT)                            { return NodeValue; }
        else if (NodeType == LOWERBOUND && NodeValue >= beta)  { return NodeValue; }

        else if (NodeType == LOWERBOUND) {alpha = std::max(alpha, NodeValue);}
        else if (NodeType == UPPERBOUND) {beta  = std::min(beta, NodeValue);}

        if (alpha >= beta) {return NodeValue;}

        BestMove = ttEntry.bestMove;
    }

    if (PlyRemaining == 0) {
        return QSearch(board, alpha, beta, Ply);
    }

    if (PlyRemaining >= 3 && !board.inCheck()){
        board.makeNullMove();
        int NullEval = -Search(board, Ply + 1, PlyRemaining - ((PlyRemaining >= 6) ? 3 : 2), -beta, -beta+1, Extensions, chess::Move::NO_MOVE);
        board.unmakeNullMove();

        if (!CanSearch) {return SEARCH_CANCELLED;}

        if (NullEval >= beta &&  std::abs(NullEval) < CheckmateThreshold) {
            return beta;
        }
    }

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, LastMove, Ply);

    // CHECK TO SEE IF THE GAME IS OVER
    if (LegalMoves.empty()){
        if (board.inCheck()){ return ImmediateMateScore + Ply; }
        else                { return 0; }
    }

    for (int i=0; i<LegalMoves.size(); i++) {
        const chess::Move move = LegalMoves[i];
        const bool isCapture = board.isCapture(move);

        board.makeMove(move);
        int Extension = CalculateExtension(board, Extensions, move);
        bool needsFullSearch = true;
        int eval = 0;

        if (i >= 3 && Extension == 0 && PlyRemaining >= 3 && !isCapture) {
            eval = -Search(board, Ply + 1, PlyRemaining - ReduceDepth, -alpha-1, -alpha, Extensions, move);
            needsFullSearch = eval > alpha;
        }

        if (needsFullSearch) {
            eval = -Search(board, Ply+1, PlyRemaining-1 + Extension, -beta, -alpha, Extensions + Extension, move);
        }

        board.unmakeMove(move);

        if (!CanSearch) { return SEARCH_CANCELLED; }

        if (eval >= beta) {
            TranspositionTable.storeTTEntry(key, beta, PlyRemaining, LOWERBOUND, move);

            if (!isCapture && !(move.typeOf() == chess::Move::PROMOTION)) {
                const bool SideToMove = board.sideToMove();

                KillerMoveTable.addKillerMoves(move, eval, board.halfMoveClock());
                HistoryTable.Update(SideToMove, move, PlyRemaining, true);
                CounterTable.Update(SideToMove, move, LastMove);
            }

            return beta;
        }

        // Negatively reward bad quiet moves in the History Table
        if (!isCapture) {
            HistoryTable.Update(board.sideToMove(), move, PlyRemaining, false);
        }

        if (eval > alpha) {
            alpha    = eval;
            BestMove = move;
            ttype    = EXACT;
        }
    }

    TranspositionTable.storeTTEntry(key, alpha, PlyRemaining, ttype, BestMove);
    return alpha;
}

int Lumina::QSearch(chess::Board& board, int alpha, int beta, int Ply) {

    if (!CanSearch) { return SEARCH_CANCELLED; }

    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.hash();
    int ttype = UPPERBOUND;
    TTEntry ttEntry;

    if (TranspositionTable.retrieveTTEntry(key, ttEntry, QSEARCHDEPTH)) {
        int NodeType  = ttEntry.nodeType;
        int NodeValue = ttEntry.value;

        if      (NodeType == UPPERBOUND && NodeValue <= alpha) { return NodeValue; }
        else if (NodeType == EXACT)                            { return NodeValue; }
        else if (NodeType == LOWERBOUND && NodeValue >= beta)  { return NodeValue; }

        else if (NodeType == LOWERBOUND) {alpha = std::max(alpha, NodeValue);}
        else if (NodeType == UPPERBOUND) {beta  = std::min(beta, NodeValue);}

        if (alpha >= beta) {return NodeValue;}
        
        BestMove = ttEntry.bestMove;
    }

    chess::Movelist LegalMoves = OrderCaptures(board, BestMove);

    int eval = Evaluation(board);

    if (eval >= beta) { return beta; }
    if (eval > alpha) { alpha = eval;}

    for (const auto &move : LegalMoves) {
        board.makeMove(move);
        int MoveEval = -QSearch(board, -beta, -alpha, Ply + 1);
        board.unmakeMove(move);

        if (!CanSearch) { return SEARCH_CANCELLED; }

        if (MoveEval >= beta) {
            TranspositionTable.storeTTEntry(key, beta, QSEARCHDEPTH, LOWERBOUND, move);
            return beta;
        }

        if (MoveEval > alpha) {
            BestMove = move;
            alpha = MoveEval;
            ttype = EXACT;
        }
    }

    TranspositionTable.storeTTEntry(key, alpha, QSEARCHDEPTH, ttype, BestMove);
    return alpha;
}