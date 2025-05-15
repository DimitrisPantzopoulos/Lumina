#include "..\Helper\HelperFunctions.h"
#include "..\ChessLib\chess.hpp"

#include "EvalHelp.h"
#include "Eval.h"

int Evaluation(const chess::Board& board){
    const int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    const int GamePhase = CalculateGamePhase(board);

    const chess::Bitboard WhitePawns   = board.pieces(chess::PieceType::PAWN,   chess::Color::WHITE);
    const chess::Bitboard BlackPawns   = board.pieces(chess::PieceType::PAWN,   chess::Color::BLACK);

    const chess::Bitboard WhiteKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::WHITE);
    const chess::Bitboard BlackKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::BLACK);

    const chess::Bitboard WhiteBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::WHITE);
    const chess::Bitboard BlackBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::BLACK);

    const chess::Bitboard WhiteRooks   = board.pieces(chess::PieceType::ROOK,   chess::Color::WHITE);
    const chess::Bitboard BlackRooks   = board.pieces(chess::PieceType::ROOK,   chess::Color::BLACK);

    const chess::Bitboard WhiteQueens  = board.pieces(chess::PieceType::QUEEN,  chess::Color::WHITE);
    const chess::Bitboard BlackQueens  = board.pieces(chess::PieceType::QUEEN,  chess::Color::BLACK);

    const chess::Bitboard WhiteKing    = board.pieces(chess::PieceType::KING,   chess::Color::WHITE);
    const chess::Bitboard BlackKing    = board.pieces(chess::PieceType::KING,   chess::Color::BLACK);

    const chess::Bitboard WhitePieces = WhitePawns | WhiteKnights | WhiteBishops | WhiteRooks | WhiteQueens | WhiteKing;
    const chess::Bitboard BlackPieces = BlackPawns | BlackKnights | BlackBishops | BlackRooks | BlackQueens | BlackKing;

    const chess::Bitboard OCC = WhitePieces | BlackPieces;

    int WhiteScore = 0;
    int BlackScore = 0;

    EvaluatePawns  (WhitePawns,   BlackPawns,   GamePhase, WhiteScore, BlackScore);
    EvaluateKnights(WhiteKnights, BlackKnights, GamePhase, WhiteScore, BlackScore);
    EvaluateBishops(WhiteBishops, BlackBishops, GamePhase, WhiteScore, BlackScore);
    EvaluateRooks  (WhiteRooks,   BlackRooks,   GamePhase, WhiteScore, BlackScore);
    EvaluateQueens (WhiteQueens,  BlackQueens,  GamePhase, WhiteScore, BlackScore);
    EvaluateKings  (WhiteKing,    BlackKing,     OCC,      GamePhase,  WhiteScore, BlackScore);

    return (WhiteScore - BlackScore) * Perspective;
}