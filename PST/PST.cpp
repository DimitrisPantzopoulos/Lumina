#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <algorithm>
#include <map>
#include "PST.h"

using namespace chess;
using namespace std;

static const array<int, 64> mg_pawn_table = {
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
};

static const array<int, 64> mg_knight_table = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

static const array<int, 64> mg_bishop_table = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

static const array<int, 64> mg_rook_table = {
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    0,  0,  0,  5,  5,  0,  0,  0
};

static const array<int, 64> mg_queen_table = {
   -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
    0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

static const array<int, 64> mg_king_table = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
};

static const array<int,64> endgame_king_table = {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50

};

static const array<int,64> EndgamePawnEndgamePST = {
     0,   0,   0,   0,   0,   0,   0,   0  ,
     70,  70,  70,  70,  70,  70,  70,  70 ,
     50,  50,  50,  50,  50,  50,  50,  50 ,
     35,  35,  35,  35,  35,  35,  35,  35 ,
     20,  20,  20,  20,  20,  20,  20,  20 ,
     10,  10,  10,  10,  10,  10,  10,  10 ,
     5,   5,   5,   5,   5,   5,   5,   5  ,
     0,   0,   0,   0,   0,   0,   0,   0  
};

int EvaluatePawnPosition(int squareIndex, const std::array<int, 64>& mg_pawn_table, const std::array<int, 64>& endgame_pawn_table, const float& weight) {
    // Interpolate between endgame and middlegame tables
    int score = static_cast<int>(weight * endgame_pawn_table[squareIndex] + (1.0f - weight) * mg_pawn_table[squareIndex]);

    return score;
}

int EvaluateKingPosition(int squareIndex, const std::array<int, 64>& endgame_king_table, const std::array<int, 64>& mg_king_table, const float& weight) {
    // Interpolate between endgame and middlegame tables
    int score = static_cast<int>(weight * endgame_king_table[squareIndex] + (1.0f - weight) * mg_king_table[squareIndex]);

    return score;
}

int PST(const Piece &piece, int squareIndex, float& endgameWeight)
{
    PieceType pieceType = piece.type();
    Color PieceColor = piece.color();

    squareIndex = PieceColor == Color::WHITE ? squareIndex : 63 - squareIndex;
    
    switch (pieceType)
    {
        case PAWN:
            return EvaluatePawnPosition(squareIndex, mg_pawn_table, EndgamePawnEndgamePST, endgameWeight);
        case KNIGHT:
            return mg_knight_table[squareIndex];
        case BISHOP:
            return mg_bishop_table[squareIndex];
        case ROOK:
            return mg_rook_table[squareIndex];
        case QUEEN:
            return mg_queen_table[squareIndex];
        case KING:
            return EvaluateKingPosition(squareIndex, endgame_king_table, mg_king_table, endgameWeight);
        default:
            return 0;
    }
}

