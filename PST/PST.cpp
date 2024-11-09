#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <algorithm>
#include <map>
#include "PST.h"

using namespace chess;
using namespace std;

static const array<int, 64> mg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 8, 7, -2, -3, 7, 3, -5,
    -12, -1, -4, 8, 7, -5, -5, -13,
    -7, -1, -1, 4, 3, -0, -7, -7,
    24, 28, 20, 15, 21, 14, 20, 22,
    92, 109, 82, 46, 60, 75, 93, 85,
    220, 228, 220, 166, 159, 198, 206, 222,
    0, 0, 0, 0, 0, 0, 0, 0
};

static const array<int, 64> eg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    17, 28, 27, 18, 17, 27, 23, 15,
    28, 39, 26, 28, 27, 25, 35, 27,
    23, 29, 24, 14, 13, 25, 23, 23,
    44, 48, 40, 15, 21, 34, 40, 42,
    97, 124, 102, 56, 70, 95, 108, 90,
    220, 223, 215, 191, 184, 193, 201, 222,
    0, 0, 0, 0, 0, 0, 0, 0
};

static const array<int, 64> mg_knight_table = {
    -110, -62, -63, -39, -37, -37, -64, -104,
    -26, -44, -29, -1, -4, -39, -43, -9,
    -44, -4, -17, 16, 20, -20, -8, -45,
    19, 36, 47, 57, 64, 38, 52, 11,
    59, 50, 93, 114, 110, 93, 55, 54,
    37, 58, 64, 96, 105, 63, 63, 22,
    -11, 5, 73, 51, 40, 66, 22, -10,
    -286, -91, -42, -6, 18, -47, -76, -299
};

static const array<int, 64> mg_bishop_table = {
    -8, 42, -12, -34, -21, -37, 45, -48,
    19, 29, 34, 5, -18, 18, 8, 28,
    23, 28, 29, 35, 45, 16, 32, -6,
    -15, 1, 8, 59, 45, 14, -18, 2,
    6, 7, 31, 51, 63, 26, 19, -8,
    39, 28, 26, 20, 9, 35, 42, 47,
    -39, -21, -1, -5, -5, -13, -18, -39,
    -51, -12, -27, 1, -11, -7, -2, -54
};
static const array<int, 64> mg_rook_table = {
    -35, -4, -1, 9, 8, -3, -3, -31,
    -39, -25, -13, -12, -14, -13, -5, -47,
    -24, 3, -23, -16, -22, -15, -3, -16,
    13, 17, 6, 4, -1, -2, 7, 0,
    52, 51, 44, 30, 27, 44, 52, 48,
    63, 78, 69, 50, 58, 58, 81, 62,
    -13, -12, 11, -3, -6, -2, -21, -14,
    92, 68, 91, 70, 73, 86, 90, 81
};
static const array<int, 64> mg_queen_table = {
    -16, -32, -23, 21, 1, -33, -35, -31,
    -15, -31, 3, -2, -7, -5, -25, 1,
    -0, 1, -15, -41, -35, -10, -6, 14,
    5, 16, -24, -22, -17, -29, 10, 0,
    36, 10, 13, 3, -0, 20, 32, 62,
    86, 70, 58, 41, 66, 75, 84, 115,
    39, -25, 66, 69, 66, 45, -33, 36,
    0, 48, 96, 87, 89, 89, 29, 14
};
static const array<int, 64> mg_king_table = {
    -67, -41, -56, -80, -73, -58, -40, -69,
    -56, -41, -38, -47, -50, -38, -41, -59,
    -67, -35, -25, -24, -25, -30, -39, -75,
    -63, -25, -4, 7, 8, -9, -24, -63,
    -36, 14, 28, 32, 28, 19, 6, -38,
    -19, 35, 49, 41, 45, 37, 26, -28,
    -21, 50, 38, 34, 27, 20, 31, -26,
    -117, -20, -12, -19, -16, -36, -35, -103
};
static const array<int, 64> eg_king_table = {
    -87, -41, -46, -50, -43, -48, -40, -89,
    -56, -21, -8, 3, 0, -8, -21, -59,
    -67, -5, 35, 56, 55, 30, -9, -75,
    -63, 5, 66, 97, 98, 61, 6, -63,
    -46, 34, 88, 112, 108, 79, 26, -48,
    -39, 45, 89, 91, 95, 77, 36, -48,
    -71, 0, 38, 34, 27, 20, -19, -76,
    -187, -80, -52, -49, -46, -76, -95, -173
};

int EvaluatePawnPosition(int squareIndex, const float& weight) {
    // Interpolate between endgame and middlegame tables
    int score = static_cast<int>(weight * eg_pawn_table[squareIndex] + (1.0f - weight) * mg_pawn_table[squareIndex]);

    return score;
}

int EvaluateKingPosition(int squareIndex, const float& weight) {
    // Interpolate between endgame and middlegame tables
    int score = static_cast<int>(weight * eg_king_table[squareIndex] + (1.0f - weight) * mg_king_table[squareIndex]);

    return score;
}

int PST(const Piece &piece, int squareIndex, float& endgameWeight)
{
    PieceType pieceType = piece.type();
    Color PieceColor = piece.color();

    squareIndex = PieceColor == Color::WHITE ? squareIndex : 63 - squareIndex;
    
    if (pieceType == chess::PieceType::PAWN) {
        return EvaluatePawnPosition(squareIndex, endgameWeight);
    } else if (pieceType == chess::PieceType::KNIGHT) {
        return mg_knight_table[squareIndex];
    } else if (pieceType == chess::PieceType::BISHOP) {
        return mg_bishop_table[squareIndex];
    } else if (pieceType == chess::PieceType::ROOK) {
        return mg_rook_table[squareIndex];
    } else if (pieceType == chess::PieceType::QUEEN) {
        return mg_queen_table[squareIndex];
    } else if (pieceType == chess::PieceType::KING) {
        return EvaluateKingPosition(squareIndex, endgameWeight);
    } else {
        return 0;
    }
}

