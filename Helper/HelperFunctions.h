#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include <vector>

constexpr int PAWN_VALUE_MG = 286;
constexpr int PAWN_VALUE_EG = 319;

constexpr int KNIGHT_VALUE_MG = 975;
constexpr int KNIGHT_VALUE_EG = 867;

constexpr int BISHOP_VALUE_MG = 952;
constexpr int BISHOP_VALUE_EG = 981;

constexpr int ROOK_VALUE_MG = 1458;
constexpr int ROOK_VALUE_EG = 1716;

constexpr int QUEEN_VALUE_MG = 3412;
constexpr int QUEEN_VALUE_EG = 3151;

constexpr int NOPAWNSHIELD_MG = 7;
constexpr int NOPAWNSHIELD_EG = 15;

constexpr int VQUEENSCOREMG = -18;
constexpr int VQUEENSCOREEG = -5;

constexpr int ISOLATEDPAWN_MG = -19;
constexpr int ISOLATEDPAWN_EG = -15;

constexpr int DOUBLEDPAWN_MG = -40;
constexpr int DOUBLEDPAWN_EG = -29;

constexpr int CENTREPAWN_MG = -4;
constexpr int CENTREPAWN_EG = -8;

constexpr int PHALANXBONUS_MG = 2;
constexpr int PHALANXBONUS_EG = 6;

constexpr int KNIGHTOUTPOST_MG = 82;
constexpr int KNIGHTOUTPOST_EG = 71;

constexpr int KNIGHTMOBILITY_MG = 35;
constexpr int KNIGHTMOBILITY_EG = 29;

constexpr int ROOKOPENFILE_MG = 43;
constexpr int ROOKOPENFILE_EG = 64;

constexpr int ROOKBACKRANK_MG = 77;
constexpr int ROOKBACKRANK_EG = 57;

constexpr int ROOKMOBILITY_MG = 16;
constexpr int ROOKMOBILITY_EG = 17;

constexpr int BISHOPOPENFILE_MG = 13;
constexpr int BISHOPOPENFILE_EG = 19;

constexpr int BISHOPFIXEDPAWNS_MG = -5;
constexpr int BISHOPFIXEDPAWNS_EG = 5;

constexpr int BISHOPMOBILITY_MG = 24;
constexpr int BISHOPMOBILITY_EG = 26;

constexpr int QUEENMOBILITY_MG = -10;
constexpr int QUEENMOBILITY_EG = -13;

constexpr int QUEENMIDDLESQUAREPRESSURE_MG = 4;
constexpr int QUEENMIDDLESQUAREPRESSURE_EG = 1;

constexpr int QUEENDISTANCE_MG = -46;
constexpr int QUEENDISTANCE_EG = -41;

static inline int TaperedEvaluation(float& weight, int WeightMG, int WeightEG){
    return static_cast<int>(weight * WeightMG + (1 - weight) * WeightEG);
}

static inline int PiecesValueEval(const int& PieceType, float weight) {
    switch (static_cast<int>(PieceType)) {
        case 0: // PAWN
            return TaperedEvaluation(weight, PAWN_VALUE_MG, PAWN_VALUE_EG);
        case 1: // KNIGHT
            return TaperedEvaluation(weight, KNIGHT_VALUE_MG, KNIGHT_VALUE_EG);
        case 2: // BISHOP
            return TaperedEvaluation(weight, BISHOP_VALUE_MG, BISHOP_VALUE_EG);
        case 3: // ROOK
            return TaperedEvaluation(weight, ROOK_VALUE_MG, ROOK_VALUE_EG);
        case 4: // QUEEN
            return TaperedEvaluation(weight, QUEEN_VALUE_MG, QUEEN_VALUE_EG);
        default:
            return  0;
    }
}

static inline int PiecesValue(const int& PieceType){
    switch (PieceType) {
        case 0: // PAWN
            return 267;
        case 1: // KNIGHT
            return 958;
        case 2: // BISHOP
            return 991;
        case 3: // ROOK
            return 1642;
        case 4: // QUEEN
            return 3361;
        default:
            return 0;
    }
}

chess::Bitboard GetPawnControlledSquares(const chess::Bitboard& pawns, const chess::Color color);

#endif