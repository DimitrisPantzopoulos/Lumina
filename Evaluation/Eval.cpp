#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\PrecomputedValues\Precomputed.h"
#include "..\Helper\HelperFunctions.h"

#include "EvalHelp.h"
#include "Eval.h"

int Evaluation(const chess::Board& board){
    const int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    // Get both pawn bitboards which is used in the Bishop Evaluation and the squares which the pawns control because that is used in 
    // Space and knight evaluation
    const chess::Bitboard WPawns = board.pieces(chess::PieceType::PAWN, chess::Color::WHITE);
    const chess::Bitboard BPawns = board.pieces(chess::PieceType::PAWN, chess::Color::BLACK);
    
    // TODO: OPTIMIZE THIS WE ONLY NEED TO CALCULATE THIS WHEN THERE ARE KNIGHTS ON THE BOARD
    const chess::Bitboard WPawnsSq = GetPawnControlledSquares(WPawns, chess::Color::WHITE);
    const chess::Bitboard BPawnsSq = GetPawnControlledSquares(BPawns, chess::Color::BLACK);

    //We get the bitboards for both sides to combine them
    const chess::Bitboard WhiteBitboard = board.us(chess::Color::WHITE);
    const chess::Bitboard BlackBitboard = board.us(chess::Color::BLACK);

    const chess::Bitboard CombinedBitboard = WhiteBitboard | BlackBitboard;

    // Now we get the indexes for all the pieces on the board so we can just check them and not have to loop over the entire board
    // Which is probably twice as efficient because we at most have to check 32 squares and not the entire 64 squares on the board
    // Also this function gets more efficient as the game progresses because less pieces = less indexes to check instead of having 
    // to check a constant 64 squares
    chess::Bitboard Indexes = CombinedBitboard;

    int WhiteScore = 0;
    int BlackScore = 0;

    float EndgameWeight = CalculateEndgameWeights(Indexes.count());

    chess::Square WKsq = board.kingSq(chess::Color::WHITE);
    chess::Square BKsq = board.kingSq(chess::Color::BLACK);

    while (Indexes != 0) {
        const int           Index = Indexes.pop();
        const chess::Square Sq    = chess::Square(Index);
        const chess::Piece  Piece = board.at(Index);
        
        const int  PieceType   = Piece.type();
        const bool Color       = Piece.color() == chess::Color::WHITE;
        const int  SquareIndex = Color ? Index : 63 - Index;
        int&       Score       = Color ? WhiteScore : BlackScore;
    
        switch (PieceType) {
            case 0: { // PAWN
                const chess::Bitboard& OurPawns       = Color ? WPawns : BPawns;
                const chess::Bitboard& TheirPawns     = Color ? BPawns : WPawns;

                Score += EvaluatePawn(Sq, TheirPawns, OurPawns, EndgameWeight, Color);
                Score += TaperedEvaluation(EndgameWeight, PAWN_VALUE_MG, PAWN_VALUE_EG);
                Score += TaperedEvaluation(EndgameWeight, mg_pawn_table[SquareIndex], eg_pawn_table[SquareIndex]);
                break;
            }
            case 1: { // KNIGHT
                const chess::Bitboard& OurPawns       = Color ? WPawns : BPawns;
                const chess::Bitboard& TheirPawns     = Color ? BPawns : WPawns;
                const chess::Bitboard& TheirPawnSq    = Color ? BPawnsSq : WPawnsSq;

                Score += EvaluateKnight(Sq, TheirPawns, OurPawns, TheirPawnSq, EndgameWeight, Color);
                Score += TaperedEvaluation(EndgameWeight, KNIGHT_VALUE_MG, KNIGHT_VALUE_EG);
                Score += mg_knight_table[SquareIndex];
                break;
            }
            case 2: { // BISHOP
                const chess::Bitboard& OurPawns       = Color ? WPawns : BPawns;
                const chess::Bitboard& TheirPawns     = Color ? BPawns : WPawns;
                const chess::Bitboard& TheirPawnSq    = Color ? BPawnsSq : WPawnsSq;

                Score += EvaluateBishop(Sq, CombinedBitboard, TheirPawns, OurPawns, TheirPawnSq, EndgameWeight, Color);
                Score += TaperedEvaluation(EndgameWeight, BISHOP_VALUE_MG, BISHOP_VALUE_EG);
                Score += mg_bishop_table[SquareIndex];
                break;
            }
            case 3: { // ROOK
                const chess::Bitboard& OurPawns       = Color ? WPawns : BPawns;
                const chess::Bitboard& TheirPawns     = Color ? BPawns : WPawns;

                Score += EvaluateRooks(Sq, TheirPawns, OurPawns, CombinedBitboard, EndgameWeight, Color);
                Score += TaperedEvaluation(EndgameWeight, ROOK_VALUE_MG, ROOK_VALUE_EG);
                Score += mg_rook_table[SquareIndex];
                break;
            }
            case 4: // QUEEN
                Score += TaperedEvaluation(EndgameWeight, QUEEN_VALUE_MG, QUEEN_VALUE_EG);
                Score += mg_queen_table[SquareIndex];
                break;

            case 5: {  
                const chess::Bitboard& OurPawns = Color ? WPawns : BPawns;

                Score += EvaluateKing(Sq, CombinedBitboard, OurPawns, EndgameWeight, Color);
                Score += TaperedEvaluation(EndgameWeight, mg_king_table[SquareIndex], eg_king_table[SquareIndex]);
                break;
            }
        }
    }
    
    WhiteScore += board.pieces(chess::PieceType::BISHOP, chess::Color::WHITE).count() > 1 ? PrecomputedBishopValues(BlackBitboard.count()) : 0;
    BlackScore += board.pieces(chess::PieceType::BISHOP, chess::Color::BLACK).count() > 1 ? PrecomputedBishopValues(WhiteBitboard.count()) : 0;

    return (WhiteScore - BlackScore) * Perspective;
}