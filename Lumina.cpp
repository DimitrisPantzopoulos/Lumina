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
#include <cmath>

#define SEARCH_CANCELLED 0.0f

#define Infinity    9999999.9f
#define Ninfinity   -Infinity

#define UPPERBOUND 1
#define EXACT      2
#define LOWERBOUND 3

#define QSEARCHDEPTH 0

#define StartingPly 0
#define ReduceDepth 2

#ifdef BENCHMARK
    int NODES_SEARCHED = 0;
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

    chess::Move BestMove = chess::Move::NO_MOVE;
    float BestEval = Ninfinity;
    int BestIndex = 0;

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, 0);

    for (int PlyRemaining = 1; PlyRemaining < 256; PlyRemaining++) {
        float eval;

        for (const auto &move : LegalMoves) {
            board.makeMove(move);
            eval = -Search(board, StartingPly, PlyRemaining, Ninfinity, Infinity, 0);
            board.unmakeMove(move);

            if (eval > BestEval && CanSearch) {
                BestEval = eval;
                BestMove = move;
            }

            if (!CanSearch) { break; }

            #ifdef BENCHMARK
                std::cout << "Searched: " << move << " Depth: " << PlyRemaining << std::endl;
            #endif
        }

        if (!CanSearch) { break; }
    }

    #ifdef BENCHMARK
        std::cout << std::endl;
        std::cout << "Searched: " << (std::round(NODES_SEARCHED / 1000)) << "K Nodes/s " << std::endl;
        std::cout << std::endl;
    #endif

    if (TimerThread.joinable()) {
        TimerThread.join();
    }

    std::cout << "info score cp " << BestEval << std::endl;
    std::cout << "bestmove " << chess::uci::moveToUci(BestMove) << std::endl;

    return BestMove;
}

float Lumina::Search(chess::Board& board, int Ply, int PlyRemaining, float alpha, float beta, int Extensions) {
    #ifdef BENCHMARK
        NODES_SEARCHED++;
    #endif

    if (!CanSearch) { return SEARCH_CANCELLED; }
    if (board.isRepetition(1)) { return 0.0f; }

    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.zobrist();
    TTEntry ttEntry;
    int ttype = UPPERBOUND;
    bool PVNode = beta - alpha > 1.0f;

    if (retrieveTTEntry(key, ttEntry, PlyRemaining)) {
        if (ttEntry.nodeType == UPPERBOUND && ttEntry.value <= alpha)     { return ttEntry.value; }
        else if (ttEntry.nodeType == EXACT)                               { return ttEntry.value; }
        else if (ttEntry.nodeType == LOWERBOUND && ttEntry.value >= beta) { return ttEntry.value; }

        BestMove = ttEntry.bestMove;
    }

    chess::GameResult State = board.isGameOver().second;

    if (PlyRemaining == 0 || State != GameResult::NONE) {
        return QSearch(board, alpha, beta, Ply);
    }

    chess::Movelist LegalMoves = OrderMoves(board, BestMove, Ply);

    for (int i = 0; i < LegalMoves.size(); i++) {
        chess::Move move = LegalMoves[i];

        board.makeMove(move);

        int Extension = CalculateExtension(board, Extensions, move);

        float eval = 0.0f;
        bool needsFullSearch = true;

        if (i >= 3 && Extension == 0 && PlyRemaining >= 3 && !board.isCapture(move)) {
            eval = -Search(board, Ply + 1, PlyRemaining - ReduceDepth, -alpha - 1.0f, -alpha, Extensions);
            needsFullSearch = eval > alpha;
        }

        if (needsFullSearch) {
            eval = -Search(board, Ply + 1, PlyRemaining - 1 + Extension, -beta, -alpha, Extensions + Extension);
        }

        board.unmakeMove(move);

        if (!CanSearch) { return SEARCH_CANCELLED; }

        if (eval >= beta) {
            storeTTEntry(key, beta, PlyRemaining, LOWERBOUND, move);

            if (!board.isCapture(move) && !(move.typeOf() == chess::Move::PROMOTION)) { KillerMoveTable.addKillerMoves(move, eval, Ply); }

            return beta;
        }

        if (eval > alpha) {
            alpha = eval;
            BestMove = move;
            ttype = EXACT;
        }
    }

    storeTTEntry(key, alpha, PlyRemaining, ttype, BestMove);

    return alpha;
}

float Lumina::QSearch(Board& board, float alpha, float beta, int Ply) {
    if (!CanSearch) { return SEARCH_CANCELLED; }

    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.zobrist();
    TTEntry ttEntry;
    int ttype = UPPERBOUND;

    if (retrieveTTEntry(key, ttEntry, QSEARCHDEPTH)) {
        if (ttEntry.nodeType == UPPERBOUND && ttEntry.value <= alpha) { return ttEntry.value; }
        else if (ttEntry.nodeType == EXACT) { return ttEntry.value; }
        else if (ttEntry.nodeType == LOWERBOUND && ttEntry.value >= beta) { return ttEntry.value; }

        BestMove = ttEntry.bestMove;
    }

    float eval = Evaluation(board, Ply);

    if (eval >= beta) { return beta; }

    if (eval > alpha) { alpha = eval; }

    chess::Movelist LegalMoves = OrderCaptures(board, BestMove);

    for (const auto &move : LegalMoves) {
        board.makeMove(move);
        float MoveEval = -QSearch(board, -beta, -alpha, Ply + 1);
        board.unmakeMove(move);

        if (!CanSearch) { return SEARCH_CANCELLED; }

        if (MoveEval >= beta) {
            storeTTEntry(key, beta, QSEARCHDEPTH, LOWERBOUND, move);
            return beta;
        }

        if (MoveEval > alpha) {
            BestMove = move;
            alpha = MoveEval;
            ttype = EXACT;
        }
    }

    storeTTEntry(key, alpha, QSEARCHDEPTH, ttype, BestMove);
    return alpha;
}