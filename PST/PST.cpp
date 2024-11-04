#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <algorithm>
#include <map>
#include "PST.h"

using namespace chess;
using namespace std;

static const array<int, 64> mg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    11, 22, 19, 7, 6, 18, 16, 8,
    -0, 9, 6, 16, 15, 5, 5, -3,
    5, 11, 10, 13, 12, 11, 5, 5,
    37, 41, 33, 27, 32, 27, 31, 34,
    105, 121, 95, 60, 74, 88, 105, 97,
    232, 240, 232, 179, 171, 211, 218, 234,
    0, 0, 0, 0, 0, 0, 0, 0
};

static const array<int, 64> eg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    31, 42, 39, 27, 26, 38, 36, 28,
    40, 49, 36, 36, 35, 35, 45, 37,
    35, 41, 35, 23, 22, 36, 35, 35,
    57, 61, 53, 27, 32, 47, 51, 54,
    110, 136, 115, 70, 84, 108, 120, 102,
    232, 235, 227, 204, 196, 206, 213, 234,
    0, 0, 0, 0, 0, 0, 0, 0
};

static const array<int, 64> mg_knight_table = {
    -66, -17, -20, 2, 5, 4, -19, -61,
    18, -2, 10, 34, 30, -0, -0, 35,
    1, 40, 26, 53, 57, 22, 35, -1,
    64, 79, 91, 98, 105, 81, 95, 57,
    103, 96, 139, 163, 159, 139, 101, 97,
    80, 104, 110, 145, 154, 109, 109, 66,
    32, 48, 119, 96, 86, 113, 66, 35,
    -242, -49, 1, 38, 62, -2, -34, -254
};

static const array<int, 64> mg_bishop_table = {
    25, 75, 18, -5, 9, -8, 78, -14,
    51, 60, 62, 29, 6, 46, 40, 62,
    57, 59, 57, 59, 69, 43, 64, 28,
    21, 33, 39, 87, 73, 45, 13, 38,
    40, 41, 62, 83, 96, 57, 54, 25,
    72, 60, 58, 54, 43, 68, 73, 82,
    -6, 11, 32, 28, 28, 21, 15, -4,
    -19, 20, 4, 34, 21, 26, 30, -21
};

static const array<int, 64> mg_rook_table = {
    5, 33, 36, 46, 44, 34, 34, 8,
    -2, 12, 22, 20, 19, 21, 32, -9,
    13, 40, 13, 17, 12, 21, 34, 22,
    50, 55, 43, 40, 35, 35, 44, 37,
    89, 90, 84, 70, 67, 84, 91, 86,
    101, 116, 108, 91, 99, 98, 120, 100,
    16, 17, 41, 28, 25, 29, 9, 15,
    130, 106, 130, 109, 112, 125, 128, 119
};

static const array<int, 64> mg_queen_table = {
    204, 188, 197, 247, 222, 186, 178, 188,
    201, 214, 251, 248, 243, 239, 221, 218,
    222, 253, 257, 247, 252, 264, 246, 238,
    246, 281, 272, 287, 292, 268, 275, 241,
    273, 277, 313, 320, 316, 319, 299, 301,
    309, 324, 344, 344, 369, 359, 339, 338,
    262, 233, 328, 340, 335, 307, 222, 258,
    228, 288, 339, 349, 351, 329, 265, 238
};

static const array<int, 64> mg_king_table = {
    -69, -41, -56, -81, -73, -58, -39, -70,
    -56, -41, -38, -47, -49, -39, -41, -60,
    -68, -35, -25, -24, -25, -30, -40, -76,
    -64, -25, -4, 8, 9, -9, -25, -64,
    -37, 13, 29, 33, 29, 19, 6, -39,
    -20, 35, 49, 42, 46, 37, 26, -30,
    -21, 49, 37, 33, 26, 19, 30, -29,
    -118, -22, -13, -20, -18, -39, -39, -107
};

static const array<int, 64> eg_king_table = {
    -89, -41, -46, -51, -43, -48, -39, -90,
    -56, -21, -8, 3, 1, -9, -21, -60,
    -68, -5, 35, 56, 55, 30, -10, -76,
    -64, 5, 66, 98, 99, 61, 5, -64,
    -47, 33, 89, 113, 109, 79, 26, -49,
    -40, 45, 89, 92, 96, 77, 36, -50,
    -71, -1, 37, 33, 26, 19, -20, -79,
    -188, -82, -53, -50, -48, -79, -99, -177
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

