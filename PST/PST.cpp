#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"
#include "PST.h"

#include <algorithm>
#include <map>

using namespace chess;
using namespace std;

static const array<int, 64> mg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    -31, -17, -8, -28, -36, -14, -27, -38,
    -42, -20, -30, -15, -16, -34, -31, -49,
    -40, -28, -30, -8, -9, -27, -43, -41,
    13, 16, 5, -0, 12, -7, -2, 5,
    141, 176, 126, 54, 81, 114, 142, 125,
    402, 404, 392, 295, 285, 346, 364, 402,
    0, 0, 0, 0, 0, 0, 0, 0
};

static const array<int, 64> eg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    -11, 3, 12, -8, -16, 6, -7, -18,
    -2, 20, 0, 5, 4, -4, 9, -9,
    -10, 2, -5, 2, 1, -2, -13, -11,
    33, 36, 25, -0, 12, 13, 18, 25,
    146, 191, 146, 64, 91, 134, 157, 130,
    402, 399, 387, 320, 310, 341, 359, 402,
    0, 0, 0, 0, 0, 0, 0, 0
};

static const array<int, 64> mg_knight_table = {
    -118, -69, -72, -50, -47, -47, -71, -113,
    -34, -53, -42, -18, -22, -52, -52, -17,
    -51, -12, -26, 1, 5, -30, -17, -53,
    12, 27, 39, 47, 53, 29, 43, 5,
    51, 45, 87, 111, 108, 88, 49, 45,
    29, 52, 58, 93, 102, 58, 57, 14,
    -19, -4, 67, 44, 34, 61, 14, -17,
    -294, -101, -51, -14, 10, -54, -86, -306
};

static const array<int, 64> mg_bishop_table = {
    -12, 38, -19, -42, -29, -45, 41, -51,
    14, 23, 25, -8, -31, 8, 3, 25,
    20, 22, 20, 22, 32, 6, 27, -9,
    -16, -4, 1, 50, 36, 8, -24, 0,
    3, 4, 25, 46, 58, 20, 17, -12,
    35, 23, 21, 17, 6, 31, 36, 45,
    -43, -26, -5, -9, -9, -16, -22, -41,
    -56, -17, -33, -4, -16, -11, -7, -58
};

static const array<int, 64> mg_rook_table = {
    -36, -8, -5, 5, 3, -7, -7, -33,
    -43, -29, -19, -21, -22, -20, -9, -50,
    -28, -1, -28, -24, -29, -20, -6, -19,
    9, 14, 2, -1, -6, -6, 3, -3,
    49, 49, 43, 29, 26, 43, 50, 45,
    60, 75, 67, 50, 58, 57, 80, 59,
    -12, -12, 13, 0, -3, 1, -19, -13,
    89, 66, 89, 68, 71, 84, 88, 78
};

static const array<int, 64> mg_queen_table = {
    -52, -68, -59, -9, -35, -71, -78, -69,
    -55, -43, -6, -9, -14, -17, -36, -39,
    -34, -4, 1, -9, -5, 8, -11, -19,
    -11, 24, 16, 31, 35, 11, 19, -16,
    17, 20, 56, 64, 60, 62, 42, 44,
    53, 68, 87, 88, 113, 102, 83, 82,
    6, -24, 71, 83, 79, 50, -35, 1,
    -29, 32, 82, 92, 94, 73, 9, -19
};

static const array<int, 64> mg_king_table = {
    -114, -44, -84, -131, -127, -83, -60, -126,
    -78, -45, -39, -51, -57, -46, -53, -91,
    -103, -27, 8, 18, 16, -3, -37, -120,
    -96, -8, 51, 82, 84, 46, -7, -95,
    -50, 57, 106, 121, 115, 89, 46, -54,
    -25, 93, 132, 128, 133, 114, 75, -41,
    -43, 94, 95, 93, 82, 65, 60, -53,
    -232, -44, -18, -17, -16, -57, -71, -212
};

static const array<int, 64> eg_king_table = {
    -134, -44, -74, -101, -97, -73, -60, -146,
    -78, -25, -9, -1, -7, -16, -33, -91,
    -103, 3, 68, 98, 96, 57, -7, -120,
    -96, 22, 121, 172, 174, 116, 23, -95,
    -60, 77, 166, 201, 195, 149, 66, -64,
    -45, 103, 172, 178, 183, 154, 85, -61,
    -93, 44, 95, 93, 82, 65, 10, -103,
    -302, -104, -58, -47, -46, -97, -131, -282
};


float PST(const Piece &piece, int squareIndex, float& endgameWeight)
{
    PieceType pieceType = piece.type();
    Color PieceColor = piece.color();

    squareIndex = PieceColor == Color::WHITE ? squareIndex : 63 - squareIndex;
    
    if (pieceType == chess::PieceType::PAWN) {
        return TaperedEvaluation(endgameWeight, mg_pawn_table[squareIndex], eg_pawn_table[squareIndex]);
    } else if (pieceType == chess::PieceType::KNIGHT) {
        return mg_knight_table[squareIndex];
    } else if (pieceType == chess::PieceType::BISHOP) {
        return mg_bishop_table[squareIndex];
    } else if (pieceType == chess::PieceType::ROOK) {
        return mg_rook_table[squareIndex];
    } else if (pieceType == chess::PieceType::QUEEN) {
        return mg_queen_table[squareIndex];
    } else if (pieceType == chess::PieceType::KING) {
        return TaperedEvaluation(endgameWeight, mg_king_table[squareIndex], eg_king_table[squareIndex]);
    } else {
        return 0.0f;
    }
}

