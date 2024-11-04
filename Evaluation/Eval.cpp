#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\PST\PST.h"
#include "..\Helper\HelperFunctions.h"

#include "EvalHelp.h"
#include "Eval.h"

#include <map>


#define ImmediateMateScore 999999

#define BISHOPPAIR 141

int Evaluation(const chess::Board& board, int Ply){
    chess::GameResult State = board.isGameOver().second;

    if(State != chess::GameResult::NONE){
        if(State == chess::GameResult::WIN)      {return (ImmediateMateScore - Ply);}
        else if(State == chess::GameResult::LOSE){return -(ImmediateMateScore - Ply);}
        else if(State == chess::GameResult::DRAW){return 0;}
    }

    int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    //Get both pawn bitboards which is used in the Bishop Evaluation and the squares which the pawns control because that is used in 
    //Space and knight evaluation + Rear Spans for each side
    chess::Bitboard WPawns = board.pieces(chess::PieceType::PAWN, chess::Color::WHITE);
    chess::Bitboard BPawns = board.pieces(chess::PieceType::PAWN, chess::Color::BLACK);
    
    chess::Bitboard WPawnsSq = GetPawnControlledSquares(WPawns, chess::Color::WHITE);
    chess::Bitboard BPawnsSq = GetPawnControlledSquares(BPawns, chess::Color::BLACK);

    //We get the bitboards for both sides to combine them
    chess::Bitboard WhiteBitboard = board.us(chess::Color::WHITE);
    chess::Bitboard BlackBitboard = board.us(chess::Color::BLACK);

    chess::Bitboard CombinedBitboard = WhiteBitboard | BlackBitboard;

    //Now we get the indexes for all the pieces on the board so we can just check them and not have to loop over the entire board
    //Which is probably twice as efficient because we at most have to check 32 squares and not the entire 64 squares on the board
    //Also this function gets more efficient as the game progresses because less pieces = less indexes to check instead of having 
    //to check a constant 64 squares
    std::vector<uint8_t> Indexes = GetIndexesFromBitBoard(CombinedBitboard);

    int WhiteScore = 0;
    int BlackScore = 0;

    int WhiteBishops = 0;
    int BlackBishops = 0;

    int endgameW = WhiteBitboard.count();
    int endgameB = BlackBitboard.count();

    // Calculate the weight for endgame influence
    float WEndgameWeight = static_cast<float>(endgameB) / 32.0f; //Get the Weight form the oppositios's side to know when to get aggresive
    float BEndgameWeight = static_cast<float>(endgameW) / 32.0f;

    chess::Square WKsq = board.kingSq(chess::Color::WHITE);
    chess::Square BKsq = board.kingSq(chess::Color::BLACK);

    for(const auto &index : Indexes){
        chess::Square Sq = chess::Square(index);

        chess::Piece Board_at = board.at(Sq); 

        bool Color = (Board_at.color() == chess::Color::WHITE);

        chess::PieceType PieceType = Board_at.type();

        if(Color){
            WhiteScore += (PiecesValue(PieceType) + PST(Board_at, index, BEndgameWeight));

            if(PieceType == chess::PieceType::PAWN){
                WhiteScore += EvaluatePawn(Sq, BPawns, WPawns, true);
            }else if(PieceType == chess::PieceType::KNIGHT){
                WhiteScore += EvaluateKnight(Sq, BPawns, WPawns, BPawnsSq, true);
            }else if(PieceType == chess::PieceType::ROOK){
                WhiteScore += EvaluateRooks(Sq, BPawns, WPawns, CombinedBitboard, BEndgameWeight, true);
            }else if(PieceType == chess::PieceType::BISHOP){
                WhiteScore += EvaluateBishop(Sq, CombinedBitboard, BPawns, WPawns, BPawnsSq, BEndgameWeight, true);
                WhiteBishops++;
            }

        }else{
            BlackScore += (PiecesValue(PieceType) + PST(Board_at, index, WEndgameWeight));

            if(PieceType == chess::PieceType::PAWN){
                BlackScore += EvaluatePawn(Sq, WPawns, BPawns, false);
            }else if(PieceType == chess::PieceType::KNIGHT){
                BlackScore += EvaluateKnight(Sq, WPawns, BPawns, WPawnsSq, false);
            }else if(PieceType == chess::PieceType::ROOK){
                BlackScore += EvaluateRooks(Sq, WPawns, BPawns, CombinedBitboard, WEndgameWeight, false);
            }else if(PieceType == chess::PieceType::BISHOP){
                BlackScore += EvaluateBishop(Sq, CombinedBitboard, WPawns, BPawns, WPawnsSq, WEndgameWeight, false);
                BlackBishops++;
            }
        }
    }

    WhiteScore += WhiteBishops > 1 ? BISHOPPAIR : 0;
    BlackScore += BlackBishops > 1 ? BISHOPPAIR : 0;

    WhiteScore += SafetyScore(WKsq, CombinedBitboard, WPawns, BEndgameWeight, true);
    BlackScore += SafetyScore(BKsq, CombinedBitboard, BPawns, WEndgameWeight, false);

    return (WhiteScore - BlackScore) * Perspective;
}