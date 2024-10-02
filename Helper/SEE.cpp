#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Evaluation\Eval.h"
#include "HelperFunctions.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#define KingValue 9999

int SEE(chess::Board& board, chess::Move move) {
    chess::Square target = move.to();
    chess::PieceType capturedPiece = board.at(target).type();
    int capturedValue = PiecesValue(capturedPiece);

    // Make the capture
    board.makeMove(move);
    chess::Color opponentColor = board.sideToMove();

    int netValue = capturedValue;

    if (board.isAttacked(target, opponentColor)) {
        //Get the movelist for captures in this position
        chess::Movelist Moves;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::CAPTURE>(Moves, board);

        // Generate recapture moves
        int MinRecaptureValue = 9999;
        chess::Move bestRecapture = chess::Move::NO_MOVE;

        for(const auto& move : Moves){
            //Get the least valuable recapture 
            if(move.to() == target){
                chess::PieceType type = board.at(move.from()).type();

                int PieceValue = PiecesValue(type);

                if(PieceValue < MinRecaptureValue){
                    bestRecapture = move;
                    MinRecaptureValue = PieceValue;
                    if(MinRecaptureValue == 100){break;}
                }
            }
        }

        if(bestRecapture != chess::Move::NO_MOVE){
            // Evaluate recaptures moves
            int recaptureValue = -SEE(board, bestRecapture);
            netValue = capturedValue + recaptureValue;
        }

    }

    // Undo the move
    board.unmakeMove(move);

    return netValue;
}
