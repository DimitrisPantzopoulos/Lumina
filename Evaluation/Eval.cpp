#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\PrecomputedValues\Precomputed.h"
#include "..\Helper\HelperFunctions.h"
#include "..\PST\PST.h"

#include "EvalHelp.h"
#include "Eval.h"
#include <map>

int Evaluation(const chess::Board& board){
    int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    //Get both pawn bitboards which is used in the Bishop Evaluation and the squares which the pawns control because that is used in 
    //Space and knight evaluation
    chess::Bitboard WPawns = board.pieces(chess::PieceType::PAWN, chess::Color::WHITE);
    chess::Bitboard BPawns = board.pieces(chess::PieceType::PAWN, chess::Color::BLACK);
    
    // TODO: OPTIMIZE THIS WE ONLY NEED TO CALCULATE THIS WHEN THERE ARE KNIGHTS ON THE BOARD
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
    uint64_t Indexes = CombinedBitboard.getBits();

    int WhiteScore = 0;
    int BlackScore = 0;

    int WhiteBishops = 0;
    int BlackBishops = 0;

    // Calculate the weight for endgame influence
    // Get the Weight form the opposition's side to know when to get aggresive
    int WhitePieceCount  = WhiteBitboard.count();
    int BlackPieceCount  = BlackBitboard.count();

    float WEndgameWeight = CalculateEndgameWeights(WhitePieceCount);
    float BEndgameWeight = CalculateEndgameWeights(BlackPieceCount);

    chess::Square WKsq = board.kingSq(chess::Color::WHITE);
    chess::Square BKsq = board.kingSq(chess::Color::BLACK);

    while (Indexes) {
        // Get the Index
        int Index = __builtin_ctzll(Indexes);

        chess::Square Sq = chess::Square(Index);

        int  PieceType = static_cast<int>(board.at(Sq).type());
        bool Color     = board.at(Sq).color() == chess::Color::WHITE;

        if(Color){
            WhiteScore += PiecesValueEval(PieceType, BEndgameWeight) + PST(PieceType, true, Index, BEndgameWeight);

            switch (PieceType){
                case 0: // PAWN
                    WhiteScore += EvaluatePawn(Sq, BPawns, WPawns, BEndgameWeight, true);
                    break;
                case 1: // KNIGHT
                    WhiteScore += EvaluateKnight(Sq, BPawns, WPawns, BPawnsSq, BEndgameWeight, true);
                    break;
                case 2: // BISHOP
                    WhiteScore += EvaluateBishop(Sq, CombinedBitboard, BPawns, WPawns, BPawnsSq, BEndgameWeight, true);
                    WhiteBishops++;
                    break;
                case 3: // ROOKS
                    WhiteScore += EvaluateRooks(Sq, BPawns, WPawns, CombinedBitboard, BEndgameWeight, true);
                    break;
                case 4:
                    WhiteScore += EvaluateQueen(Sq, board, BPawns, CombinedBitboard, chess::Color::BLACK, BEndgameWeight);
                    break;
            }

        }else{
            BlackScore += PiecesValueEval(PieceType, WEndgameWeight) + PST(PieceType, false, Index, WEndgameWeight);

            switch (PieceType){
                case 0: // PAWN
                    BlackScore += EvaluatePawn(Sq, WPawns, BPawns, WEndgameWeight, false);
                    break;
                case 1: // KNIGHT
                    BlackScore += EvaluateKnight(Sq, WPawns, BPawns, WPawnsSq, WEndgameWeight, false);
                    break;
                case 2: // BISHOP
                    BlackScore += EvaluateBishop(Sq, CombinedBitboard, WPawns, BPawns, WPawnsSq, WEndgameWeight, false);
                    BlackBishops++;
                    break;
                case 3: // ROOK 
                    BlackScore += EvaluateRooks(Sq, WPawns, BPawns, CombinedBitboard, WEndgameWeight, false);
                    break;
                case 4: // QUEEN
                    BlackScore += EvaluateQueen(Sq, board, WPawns, CombinedBitboard, chess::Color::WHITE, WEndgameWeight);
                    break;
            }
        }

        Indexes &= Indexes - 1;
    }

    WhiteScore += WhiteBishops > 1 ? PrecomputedBishopValues(BlackPieceCount) : 0;
    BlackScore += BlackBishops > 1 ? PrecomputedBishopValues(WhitePieceCount) : 0;

    WhiteScore += SafetyScore(WKsq, CombinedBitboard, WPawns, BEndgameWeight, true);
    BlackScore += SafetyScore(BKsq, CombinedBitboard, BPawns, WEndgameWeight, false);

    return (WhiteScore - BlackScore) * Perspective;
}