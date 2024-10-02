#include "ChessLib\chess-library-master\include\chess.hpp"
#include "Dimibot.h"
#include "Evaluation/Eval.h"
#include "MoveOrdering/Orderer.h"
#include "Helper/SEE.h"
#include "Helper/HelperFunctions.h"
#include "TT/TT.h"

#include <iostream>
#include <chrono>

using namespace std::chrono;

#define Infinity  9999999
#define Ninfinity -Infinity
#define StartingPly 0
#define ReduceDepth 2
#define Delta 55

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

chess::Move Dimibot::Think(Board& board, int Milliseconds) {
    // Record the start time
    auto start = high_resolution_clock::now();
    
    // Calculate the end time based on the given milliseconds
    auto endTime = start + milliseconds(Milliseconds);

    chess::Move BestMove;
    int BestEval = Ninfinity;

    // Generate Legal Moves and the No Move is just for filler
    chess::Movelist LegalMoves = OrderMoves(board, BestMove);

    for (int PlyRemaining = 1; PlyRemaining < 256; PlyRemaining++) {
        bool timeExpired = false;
        
        for (const auto &move : LegalMoves) {

            auto now = high_resolution_clock::now();

            if (now >= endTime) { 
                timeExpired = true;
                break; // Exit the inner loop
            }
            
            board.makeMove(move);
            int eval = -Search(board, StartingPly, PlyRemaining, Ninfinity, Infinity, 0);
            board.unmakeMove(move);

            if (eval > BestEval) {
                BestEval = eval;
                BestMove = move;
                BestMoveFound = BestMove;
            }
        }
        
        if (timeExpired) {
            break; // Exit the outer loop
        }

    }

    std::cout << "info score cp " << BestEval << std::endl;
    std::cout << "bestmove " << chess::uci::moveToUci(BestMove) << std::endl;

    return BestMove;
}

int Dimibot::Search(chess::Board& board, int Ply ,int PlyRemaining, int alpha, int beta, int Extensions){

    if(board.isRepetition(1)){
        return 0;
    }

    //TranspositionTable Lookup
    chess::Move BestMove = BestMoveFound;
    uint64_t key = board.zobrist();
    TTEntry ttEntry;

    int ttype = 1; //UPPERBOUND

    if (retrieveTTEntry(key, ttEntry, PlyRemaining)){
        BestMove = ttEntry.bestMove;

        if (ttEntry.nodeType == 1 && ttEntry.value <= alpha) { // UPPERBOUND 
            return ttEntry.value;
        } else if (ttEntry.nodeType == 2) { // EXACT
            return ttEntry.value;
        } else if (ttEntry.nodeType == 3 && ttEntry.value >= beta) { // LOWERBOUND
            return ttEntry.value;
        }
    }

    chess::GameResult State = board.isGameOver().second;

    if (PlyRemaining == 0 || State != GameResult::NONE){
        return QSearch(board, alpha, beta, Ply);
    }


    //Generate Legal Moves
    chess::Movelist LegalMoves = OrderMoves(board, BestMove);

    int MoveEval = 0;

    //Search all possible moves until Depth runs out
    for (int i=0;i<LegalMoves.size();i++){
        chess::Move move = LegalMoves[i];

        board.makeMove(move);

        //Check Extensions
        int Extension = CalculateExtension(board, Extensions, move);

        bool needsFullSearch = true;
        
        if(i < 3 && Extension == 0 && PlyRemaining >= 3 && !board.isCapture(move)){
            // Do a Narrow Search for all the other moves + LMR
            MoveEval = -Search(board, Ply+1, PlyRemaining - ReduceDepth, -alpha-1, -alpha, Extensions);

            needsFullSearch = MoveEval > alpha;
        }
        
        if(needsFullSearch){
            //Search the Move fully 
            MoveEval = -Search(board, Ply+1, PlyRemaining-1 + Extension, -beta, -alpha, Extensions + Extension);
        }

        board.unmakeMove(move);

        if (MoveEval >= beta){
            storeTTEntry(key, beta, PlyRemaining, 3, move); //LOWERBOUND

            //Beta cut off Move was too good the opponent will avoid this position
            return beta;
        }

        //Update alpha
        if (alpha < MoveEval){
            alpha = MoveEval;
            BestMove = move;
            ttype = 2; //EXACT
        }
    }

    storeTTEntry(key, alpha, PlyRemaining, ttype, BestMove);
    return alpha;
}

int Dimibot::QSearch(Board& board, int alpha, int beta, int Ply){
    int eval = Evaluation(board, Ply);

    if(eval >= beta){
        return beta;
    }

    alpha = std::max(alpha, eval);
    
    //Generate Legal Moves
    chess::Movelist LegalMoves = OrderCaptures(board);

    //Search all possible moves until Depth runs out
    for (const auto &move : LegalMoves){
        
        int MaterialGain = PiecesValue(board.at(move.to()).type());

        // Delta pruning: Skip moves that don't significantly change the evaluation
        if (eval + MaterialGain + Delta <= alpha) {
            continue;
        }
        
        board.makeMove(move);
        int MoveEval = -QSearch(board, -beta, -alpha, Ply++);
        board.unmakeMove(move);

        if (MoveEval >= beta){
            //Beta cut off Move was too good the opponent will avoid this position
            return beta;
        }

        //Update alpha
        alpha = std::max(alpha, MoveEval);
    } 

    return alpha;
}
