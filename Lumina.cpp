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

#define SEARCH_CANCELLED 0

#define Infinity    9999999
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

void Timer(int Milliseconds, std::atomic<bool>& CanSearch){
    std::this_thread::sleep_for(std::chrono::milliseconds(Milliseconds));
    CanSearch = false;
}

int CalculateExtension(chess::Board& board, int &Extensions, const chess::Move& move){
    int Extension = 0;

    chess::PieceType Type = board.at(move.from()).type();
    chess::Rank MoveRank = move.to().rank();

    if (Extensions < 16){
        Extension += board.inCheck() ? 1 : 0;
        Extension += Type == chess::PieceType::PAWN && (MoveRank == chess::Rank::RANK_2 || MoveRank == chess::Rank::RANK_7);
    }

    return Extension;
}

chess::Move Lumina::Think(Board& board, int Milliseconds) {
    // Set CanSearch to true so we can search
    CanSearch = true;

    // Start timer to keep track of how long we are searching for
    auto TimerThread = std::thread(Timer, Milliseconds, std::ref(CanSearch));

    chess::Move BestMove = chess::Move::NO_MOVE;
    int BestEval  = Ninfinity;
    int BestIndex = 0;

    // Generate Legal Moves
    chess::Movelist LegalMoves = OrderMoves(board, BestMove, 0);

    for (int PlyRemaining = 1; PlyRemaining < 256; PlyRemaining++) {
        int eval;

        for (const auto &move : LegalMoves) {
            board.makeMove(move);
            eval = -Search(board, StartingPly, PlyRemaining, Ninfinity, Infinity, 0);
            board.unmakeMove(move);
            
            if (eval > BestEval && CanSearch) {
                BestEval = eval;
                BestMove = move;
            }

            // Exit the search if time is up to keep up with time
            if (!CanSearch) {break;}

            #ifdef BENCHMARK
                std::cout << "Searched: " << move << " Depth: " << PlyRemaining << std::endl;
            #endif
        }

        // Exit the search to keep up with timer
        if (!CanSearch) {break;}
    }

    #ifdef BENCHMARK
        std::cout << std::endl;
        std::cout << "Searched: " << (std::round(NODES_SEARCHED / 1000)) << "K Nodes/s " << std::endl;
        std::cout << std::endl;
    #endif

    // Clean up timer thread
    if (TimerThread.joinable()) {
        TimerThread.join();
    }

    std::cout << "info score cp " << BestEval << std::endl;
    std::cout << "bestmove " << chess::uci::moveToUci(BestMove) << std::endl;

    return BestMove;
}

int Lumina::Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions){
    static const std::array<int, 5> QuietsToSearch = {0, 4, 5, 15, 25};
    int QuietsSearched = QuietsToSearch[std::max(4, PlyRemaining)];

    #ifdef BENCHMARK
        NODES_SEARCHED++;
    #endif

    if(!CanSearch){return SEARCH_CANCELLED;}
    if(board.isRepetition(1)){return 0;}

    // TranspositionTable Lookup
    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.zobrist();
    TTEntry ttEntry;
    int ttype = UPPERBOUND;
    bool PVNode = beta - alpha > 1;

    if (retrieveTTEntry(key, ttEntry, PlyRemaining)){
        if        (ttEntry.nodeType == UPPERBOUND && ttEntry.value <= alpha) { return ttEntry.value; } // UPPERBOUND
        else if   (ttEntry.nodeType == EXACT)                                { return ttEntry.value; } // EXACT
        else if   (ttEntry.nodeType == LOWERBOUND && ttEntry.value >= beta)  { return ttEntry.value; } // LOWERBOUND

        BestMove = ttEntry.bestMove;
    }

    chess::GameResult State = board.isGameOver().second;

    if (PlyRemaining == 0 || State != GameResult::NONE){
        return QSearch(board, alpha, beta, Ply);
    }

    // Generate Legal Moves
    chess::Movelist LegalMoves = OrderMoves(board, BestMove, Ply);

    // Search all possible moves until Depth runs out
    for (int i=0;i<LegalMoves.size();i++){
        chess::Move move = LegalMoves[i];

        board.makeMove(move);

        // Check Extensions
        int Extension = CalculateExtension(board, Extensions, move);

        int eval = 0;
        bool needsFullSearch = true;

        if(i >= 3 && Extension == 0 && PlyRemaining >= 3 && !board.isCapture(move)){
            // Do a Narrow Search for all the other moves + LMR
            eval = -Search(board, Ply+1, PlyRemaining - ReduceDepth, -alpha-1, -alpha, Extensions);

            needsFullSearch = eval > alpha;
        }
        
        if(needsFullSearch){
            // Search the Move fully 
            eval = -Search(board, Ply + 1, PlyRemaining - 1 + Extension, -beta, -alpha, Extensions + Extension);
        }

        board.unmakeMove(move);

        if(!CanSearch){return SEARCH_CANCELLED;}

        if (eval >= beta){
            storeTTEntry(key, beta, PlyRemaining, LOWERBOUND, move);

            // Add to Killermoves
            if(!board.isCapture(move)) {KillerMoveTable.addKillerMoves(move, eval, Ply);}

            // Beta cut off Move was too good the opponent will avoid this position
            return beta;
        }

        // Update alpha
        if (eval > alpha){
            alpha    = eval;
            BestMove = move;
            ttype    = EXACT;
        }

        if(!PVNode && PlyRemaining <= 4 && !board.isCapture(move) && (QuietsSearched == 1 || eval + 127 * PlyRemaining < alpha))
        {
            break;
        }
    }

    storeTTEntry(key, alpha, PlyRemaining, ttype, BestMove);
    return alpha;
}

int Lumina::QSearch(Board& board, int alpha, int beta, int Ply){
    if(!CanSearch){return SEARCH_CANCELLED;}

    // TranspositionTable Lookup
    chess::Move BestMove = chess::Move::NO_MOVE;
    uint64_t key = board.zobrist();
    TTEntry ttEntry;
    int ttype = UPPERBOUND;

    if (retrieveTTEntry(key, ttEntry, QSEARCHDEPTH)){
        if        (ttEntry.nodeType == UPPERBOUND && ttEntry.value <= alpha) { return ttEntry.value; } // UPPERBOUND
        else if   (ttEntry.nodeType == EXACT)                                { return ttEntry.value; } // EXACT
        else if   (ttEntry.nodeType == LOWERBOUND && ttEntry.value >= beta)  { return ttEntry.value; } // LOWERBOUND

        BestMove = ttEntry.bestMove;
    }

    int eval = Evaluation(board, Ply);

    if(eval >= beta) { return beta; }

    if (eval > alpha){ alpha = eval; }
    
    // Generate Legal Moves
    chess::Movelist LegalMoves = OrderCaptures(board, BestMove);

    // Search all possible moves until Depth runs out
    for (const auto &move : LegalMoves){
        board.makeMove(move);
        int MoveEval = -QSearch(board, -beta, -alpha, Ply+1);
        board.unmakeMove(move);

        if(!CanSearch){return SEARCH_CANCELLED;}

        if (MoveEval >= beta){
            // Store in TT
            storeTTEntry(key, beta, QSEARCHDEPTH, LOWERBOUND, move);

            // Beta cut off Move was too good the opponent will avoid this position
            return beta;
        }

        // Update alpha
        if (MoveEval > alpha){
            BestMove = move;
            alpha = MoveEval;
            
            ttype = 2;
        }
    } 

    storeTTEntry(key, alpha, QSEARCHDEPTH, ttype, BestMove);
    return alpha;
}
