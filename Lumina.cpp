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

void Timer(int Milliseconds, std::atomic<bool>& CanSearch) {
    std::this_thread::sleep_for(std::chrono::milliseconds(Milliseconds));
    CanSearch = false;
}

chess::Move Lumina::Think(Board& board, int Milliseconds) {
    // Launch Timer thread
    CanSearch = true;
    auto TimerThread = std::thread(Timer, Milliseconds, std::ref(CanSearch));

    // Decay History Table
    HistoryTable.Decay();
    
    chess::Move BestMove = chess::Move::NO_MOVE;
    int         BestEval = Ninfinity;

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, 0);

    for (int PlyRemaining = 1; PlyRemaining < 256; PlyRemaining++) {
        BestEval = Ninfinity;
        std::vector<int> MoveScores;
        MoveScores.reserve(LegalMoves.size());

        for (const auto &move : LegalMoves) {
            board.makeMove(move);
            int eval = -Search(board, StartingPly, PlyRemaining, Ninfinity, Infinity, 0);
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

        LegalMoves = OrderFromIteration(LegalMoves, MoveScores);
    }

    if (TimerThread.joinable()) {
        TimerThread.join();
    }

    std::cout << "info score cp " << BestEval << std::endl;
    std::cout << "bestmove " << chess::uci::moveToUci(BestMove) << std::endl;

    return BestMove;
}

int Lumina::Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions) {
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

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, Ply);

    // CHECK TO SEE IF THE GAME IS OVER
    if (LegalMoves.empty()){
        if (board.inCheck()){ return ImmediateMateScore + Ply; }
        else                { return 0; }
    }

    for (int i=0; i<LegalMoves.size(); i++) {
        chess::Move move = LegalMoves[i];

        board.makeMove(move);

        int Extension = CalculateExtension(board, Extensions, move);
        bool needsFullSearch = true;
        int eval = 0;

        if (i >= 3 && Extension == 0 && PlyRemaining >= 3 && !board.isCapture(move)) {
            eval = -Search(board, Ply + 1, PlyRemaining - ReduceDepth, -alpha-1, -alpha, Extensions);
            needsFullSearch = eval > alpha;
        }

        if (needsFullSearch) {
            eval = -Search(board, Ply+1, PlyRemaining-1 + Extension, -beta, -alpha, Extensions + Extension);
        }

        board.unmakeMove(move);

        if (!CanSearch) { return SEARCH_CANCELLED; }

        if (eval >= beta) {
            TranspositionTable.storeTTEntry(key, beta, PlyRemaining, LOWERBOUND, move);

            if (!board.isCapture(move) && !(move.typeOf() == chess::Move::PROMOTION)) {
                KillerMoveTable.addKillerMoves(move, eval, Ply);
                HistoryTable.Update(board.sideToMove(), move, PlyRemaining);
            }

            return beta;
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