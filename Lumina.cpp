#include "ChessLib\chess-library-master\include\chess.hpp"
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

#ifdef LDEBUG
    #include <cmath>
    int DEBUG_SEARCH_NODES  = 0;
    int DEBUG_QSEARCH_NODES = 0;
#endif

void Timer(int Milliseconds, std::atomic<bool>& CanSearch) {
    std::this_thread::sleep_for(std::chrono::milliseconds(Milliseconds));
    CanSearch = false;
}

int CalculateExtension(chess::Board& board, int &Extensions, const chess::Move& move) {
    int Extension = 0;

    chess::PieceType Type = board.at(move.from()).type();
    chess::Rank MoveRank = move.to().rank();

    if (Extensions < 16) {
        Extension += board.inCheck() ? 1 : 0;
        Extension += Type == chess::PieceType::PAWN && (MoveRank == chess::Rank::RANK_2 || MoveRank == chess::Rank::RANK_7);
    }

    return Extension;
}

chess::Move Lumina::Think(Board& board, int Milliseconds) {
    CanSearch = true;

    auto TimerThread = std::thread(Timer, Milliseconds, std::ref(CanSearch));
    chess::Move BestMove;
    int BestEval = Ninfinity;
    int LastValidEval = 0;

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, 0);

    for (int PlyRemaining = 1; PlyRemaining < 256; PlyRemaining++) {
        BestEval = Ninfinity;

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

            #ifdef LDEBUG
                std::cout << "Searched: " << move << " Depth: " << PlyRemaining << " Eval: " << eval << std::endl;
            #endif
        }

        if (BestEval != Ninfinity) {
            LastValidEval = BestEval;
        }

        #ifdef LDEBUG
            std::cout << "Searched Depth: " << PlyRemaining << " BestMove: " << BestMove << " Eval: " << BestEval << std::endl;
        #endif

        if (!CanSearch) { 
            break; 
        }

        LegalMoves = OrderMoves(board, BestMove, 0);
    }

    #ifdef LDEBUG
        std::cout << std::endl;
        std::cout << "Searched SEARCH  NODES: " << (std::round(DEBUG_SEARCH_NODES  / 1000)) << "K Nodes/s " << std::endl;
        std::cout << "Searched QSEARCH NODES: " << (std::round(DEBUG_QSEARCH_NODES / 1000)) << "K Nodes/s " << std::endl;
        std::cout << "Searched Total   NODES: " << (std::round(DEBUG_SEARCH_NODES  / 1000) + std::round(DEBUG_QSEARCH_NODES / 1000)) << "K Nodes/s " << std::endl;
        std::cout << std::endl;
    #endif

    if (TimerThread.joinable()) {
        TimerThread.join();
    }

    if (BestEval == Ninfinity) {
        BestEval = LastValidEval;
    }

    std::cout << "info score cp " << BestEval << std::endl;
    std::cout << "bestmove " << chess::uci::moveToUci(BestMove) << std::endl;

    return BestMove;
}

int Lumina::Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions) {
    #ifdef LDEBUG
        DEBUG_SEARCH_NODES++;
    #endif

    if (!CanSearch || board.isRepetition(1)) { return SEARCH_CANCELLED; }
    
    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.zobrist();
    TTEntry ttEntry;
    int ttype = UPPERBOUND;

    if (TT.retrieveTTEntry(key, ttEntry, PlyRemaining)) {
        if      (ttEntry.nodeType == UPPERBOUND && ttEntry.value <= alpha){ return ttEntry.value; }
        else if (ttEntry.nodeType == EXACT)                               { return ttEntry.value; }
        else if (ttEntry.nodeType == LOWERBOUND && ttEntry.value >= beta) { return ttEntry.value; }

        BestMove = ttEntry.bestMove;
    }

    chess::GameResult State = board.isGameOver().second;

    if (PlyRemaining == 0 || State != GameResult::NONE) {
        return QSearch(board, alpha, beta, Ply);
    }

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, Ply);

    for (int i=0; i<LegalMoves.size(); i++) {
        chess::Move move = LegalMoves[i];

        board.makeMove(move);

        int Extension = CalculateExtension(board, Extensions, move);
        bool needsFullSearch = true;
        int eval = 0;

        if (i >= 3 && Extension == 0 && PlyRemaining >= 3 && !board.isCapture(move)) {
            eval = -Search(board, Ply+1, PlyRemaining - ReduceDepth, -alpha-1, -alpha, Extensions);
            needsFullSearch = eval > alpha;
        }

        if (needsFullSearch) {
            eval = -Search(board, Ply+1, PlyRemaining-1 + Extension, -beta, -alpha, Extensions + Extension);
        }

        board.unmakeMove(move);

        if (!CanSearch) { return SEARCH_CANCELLED; }

        if (eval >= beta) {
            TT.storeTTEntry(key, beta, PlyRemaining, LOWERBOUND, move);

            if (!board.isCapture(move) && !(move.typeOf() == chess::Move::PROMOTION)) { KillerMoveTable.addKillerMoves(move, eval, Ply); }

            return beta;
        }

        if (eval > alpha) {
            alpha    = eval;
            BestMove = move;
            ttype    = EXACT;
        }
    }

    TT.storeTTEntry(key, alpha, PlyRemaining, ttype, BestMove);
    return alpha;
}

int Lumina::QSearch(chess::Board& board, int alpha, int beta, int Ply) {
    #ifdef LDEBUG
        DEBUG_QSEARCH_NODES++;
    #endif

    if (!CanSearch) { return SEARCH_CANCELLED; }

    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.zobrist();
    int ttype = UPPERBOUND;
    TTEntry ttEntry;

    if (TT.retrieveTTEntry(key, ttEntry, QSEARCHDEPTH)) {
        if      (ttEntry.nodeType == UPPERBOUND && ttEntry.value <= alpha){ return ttEntry.value; }
        else if (ttEntry.nodeType == EXACT)                               { return ttEntry.value; }
        else if (ttEntry.nodeType == LOWERBOUND && ttEntry.value >= beta) { return ttEntry.value; }

        BestMove = ttEntry.bestMove;
    }

    int eval = Evaluation(board, Ply);

    if (eval >= beta) { return beta; }
    if (eval > alpha) { alpha = eval;}

    chess::Movelist LegalMoves = OrderCaptures(board, BestMove);

    for (const auto &move : LegalMoves) {
        board.makeMove(move);
        int MoveEval = -QSearch(board, -beta, -alpha, Ply + 1);
        board.unmakeMove(move);

        if (!CanSearch) { return SEARCH_CANCELLED; }

        if (MoveEval >= beta) {
            TT.storeTTEntry(key, beta, QSEARCHDEPTH, LOWERBOUND, move);
            return beta;
        }

        if (MoveEval > alpha) {
            BestMove = move;
            alpha = MoveEval;
            ttype = EXACT;
        }
    }

    TT.storeTTEntry(key, alpha, QSEARCHDEPTH, ttype, BestMove);
    return alpha;
}