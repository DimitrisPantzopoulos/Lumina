#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"
#include "..\EvaluationFeatures\Features.h"

#include "EvalHelp.h"
#include "Eval.h"

int Evaluation(const chess::Board& board)
{
    int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    constexpr uint64_t NOT_HFILE = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE = ~0x0101010101010101ULL;

    // Get Bitboards for evaluation
    const chess::Bitboard WPawns = board.pieces(chess::PieceType::PAWN, chess::Color::WHITE);
    const chess::Bitboard BPawns = board.pieces(chess::PieceType::PAWN, chess::Color::BLACK);

    const chess::Bitboard WKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::WHITE);
    const chess::Bitboard BKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::BLACK);
    
    const chess::Bitboard WBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::WHITE);
    const chess::Bitboard BBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::BLACK);

    const chess::Bitboard WRooks = board.pieces(chess::PieceType::ROOK, chess::Color::WHITE);
    const chess::Bitboard BRooks = board.pieces(chess::PieceType::ROOK, chess::Color::BLACK);
    
    const chess::Bitboard WQueen = board.pieces(chess::PieceType::QUEEN, chess::Color::WHITE);
    const chess::Bitboard BQueen = board.pieces(chess::PieceType::QUEEN, chess::Color::BLACK);

    const chess::Bitboard WKing = board.pieces(chess::PieceType::KING, chess::Color::WHITE);
    const chess::Bitboard BKing = board.pieces(chess::PieceType::KING, chess::Color::BLACK);

    const chess::Bitboard WPawnsThreats = (WPawns & NOT_HFILE) << 9 | (WPawns & NOT_AFILE) << 7;
    const chess::Bitboard BPawnsThreats = (BPawns & NOT_AFILE) >> 9 | (BPawns & NOT_HFILE) >> 7;

    //We get the bitboards for both sides to combine them
    const chess::Bitboard WhiteBitboard = WPawns | WKnights | WBishops | WRooks | WQueen | WKing;
    const chess::Bitboard BlackBitboard = BPawns | BKnights | BBishops | BRooks | BQueen | BKing;

    const chess::Bitboard CombinedBitboard = WhiteBitboard | BlackBitboard;

    // Now we get the indexes for all the pieces on the board so we can just check them and not have to loop over the entire board
    // Which is probably twice as efficient because we at most have to check 32 squares and not the entire 64 squares on the board
    // Also this function gets more efficient as the game progresses because less pieces = less indexes to check instead of having 
    // to check a constant 64 squares
    chess::Bitboard Indexes = CombinedBitboard;

    int WhiteScore = 0;
    int BlackScore = 0;

    // Calculate the weight for endgame influence
    // Get the Weight form the opposition's side to know when to get aggresive
    int WhitePieceCount  = WhiteBitboard.count();
    int BlackPieceCount  = BlackBitboard.count();

    float WMiddlegameWeight = static_cast<float>(WhitePieceCount) / 32.0f;
    float BMiddlegameWeight = static_cast<float>(BlackPieceCount) / 32.0f;

    // Structural Evaluations
    EvaluatePawns(WPawns, BPawns, WhiteScore, BlackScore, WMiddlegameWeight, BMiddlegameWeight);
    EvaluateKnights(WKnights, BKnights, WPawns, BPawns, WPawnsThreats, BPawnsThreats, WhiteScore, BlackScore, WMiddlegameWeight, BMiddlegameWeight);
    EvaluateBishops(WBishops, BBishops, WPawns, BPawns, WPawnsThreats, BPawnsThreats, WhiteScore, BlackScore, WMiddlegameWeight, BMiddlegameWeight);
    EvaluateRooks(WRooks, BRooks, WPawns, BPawns, WhiteScore, BlackScore, WMiddlegameWeight, BMiddlegameWeight);

    while (Indexes != 0) {
        const int Index = Indexes.pop();
        const chess::Square Sq(Index);
        const chess::Piece piece = board.at(Sq);
        const int PieceType = piece.type();
        const bool Color = piece.color() == chess::Color::WHITE;
    
        const float EndgameWeight  = Color ? WMiddlegameWeight : BMiddlegameWeight;
        const int   PSTIndex       = Color ? Index          : 63 - Index;
        int&        Score          = Color ? WhiteScore     : BlackScore;

        switch (PieceType) {
            case 0: // PAWN
                Score += EvaluatePawn(Sq, EndgameWeight, Color, PSTIndex);
                break;
        
            case 1: { // KNIGHT
                const chess::Bitboard& EnemyPawnThreats = Color ? BPawnsThreats : WPawnsThreats;
                Score += EvaluateKnight(Sq, EnemyPawnThreats, EndgameWeight, PSTIndex, Color);
                break;
            }
        
            case 2:
                Score += EvaluateBishop(Sq, CombinedBitboard, EndgameWeight, PSTIndex, Color);
                break;
        
            case 3:
                Score += EvaluateRook(Sq, CombinedBitboard, EndgameWeight, PSTIndex, Color);
                break;
        
            case 4:
                Score += EvaluateQueen(Sq, EndgameWeight, PSTIndex, Color);
                break;
        
            case 5: {
                const chess::Bitboard& FriendlyPawns = Color ? WPawns : BPawns;
                Score += EvaluateKing(Sq, FriendlyPawns, CombinedBitboard, EndgameWeight, PSTIndex, Color);
                break;
            }
        
            default:
                break;
        }        
    }

    return (WhiteScore - BlackScore) * Perspective;
}