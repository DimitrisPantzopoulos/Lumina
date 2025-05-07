#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr std::array<int, 64> mg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    -31, -17, -8, -28, -36, -14, -27, -38,
    -42, -20, -30, -15, -16, -34, -31, -49,
    -40, -28, -30, -8, -9, -27, -43, -41,
    13, 16, 5, -0, 12, -7, -2, 5,
    141, 176, 126, 54, 81, 114, 142, 125,
    402, 404, 392, 295, 285, 346, 364, 402,
    0, 0, 0, 0, 0, 0, 0, 0
};

constexpr std::array<int, 64> eg_pawn_table = {
    0, 0, 0, 0, 0, 0, 0, 0,
    -11, 3, 12, -8, -16, 6, -7, -18,
    -2, 20, 0, 5, 4, -4, 9, -9,
    -10, 2, -5, 2, 1, -2, -13, -11,
    33, 36, 25, -0, 12, 13, 18, 25,
    146, 191, 146, 64, 91, 134, 157, 130,
    402, 399, 387, 320, 310, 341, 359, 402,
    0, 0, 0, 0, 0, 0, 0, 0
};

constexpr std::array<int, 64> mg_knight_table = {
    -118, -69, -72, -50, -47, -47, -71, -113,
    -34, -53, -42, -18, -22, -52, -52, -17,
    -51, -12, -26, 1, 5, -30, -17, -53,
    12, 27, 39, 47, 53, 29, 43, 5,
    51, 45, 87, 111, 108, 88, 49, 45,
    29, 52, 58, 93, 102, 58, 57, 14,
    -19, -4, 67, 44, 34, 61, 14, -17,
    -294, -101, -51, -14, 10, -54, -86, -306
};

constexpr std::array<int, 64> mg_bishop_table = {
    -12, 38, -19, -42, -29, -45, 41, -51,
    14, 23, 25, -8, -31, 8, 3, 25,
    20, 22, 20, 22, 32, 6, 27, -9,
    -16, -4, 1, 50, 36, 8, -24, 0,
    3, 4, 25, 46, 58, 20, 17, -12,
    35, 23, 21, 17, 6, 31, 36, 45,
    -43, -26, -5, -9, -9, -16, -22, -41,
    -56, -17, -33, -4, -16, -11, -7, -58
};

constexpr std::array<int, 64> mg_rook_table = {
    -36, -8, -5, 5, 3, -7, -7, -33,
    -43, -29, -19, -21, -22, -20, -9, -50,
    -28, -1, -28, -24, -29, -20, -6, -19,
    9, 14, 2, -1, -6, -6, 3, -3,
    49, 49, 43, 29, 26, 43, 50, 45,
    60, 75, 67, 50, 58, 57, 80, 59,
    -12, -12, 13, 0, -3, 1, -19, -13,
    89, 66, 89, 68, 71, 84, 88, 78
};

constexpr std::array<int, 64> mg_queen_table = {
    -52, -68, -59, -9, -35, -71, -78, -69,
    -55, -43, -6, -9, -14, -17, -36, -39,
    -34, -4, 1, -9, -5, 8, -11, -19,
    -11, 24, 16, 31, 35, 11, 19, -16,
    17, 20, 56, 64, 60, 62, 42, 44,
    53, 68, 87, 88, 113, 102, 83, 82,
    6, -24, 71, 83, 79, 50, -35, 1,
    -29, 32, 82, 92, 94, 73, 9, -19
};

constexpr std::array<int, 64> mg_king_table = {
    -114, -44, -84, -131, -127, -83, -60, -126,
    -78, -45, -39, -51, -57, -46, -53, -91,
    -103, -27, 8, 18, 16, -3, -37, -120,
    -96, -8, 51, 82, 84, 46, -7, -95,
    -50, 57, 106, 121, 115, 89, 46, -54,
    -25, 93, 132, 128, 133, 114, 75, -41,
    -43, 94, 95, 93, 82, 65, 60, -53,
    -232, -44, -18, -17, -16, -57, -71, -212
};

constexpr std::array<int, 64> eg_king_table = {
    -134, -44, -74, -101, -97, -73, -60, -146,
    -78, -25, -9, -1, -7, -16, -33, -91,
    -103, 3, 68, 98, 96, 57, -7, -120,
    -96, 22, 121, 172, 174, 116, 23, -95,
    -60, 77, 166, 201, 195, 149, 66, -64,
    -45, 103, 172, 178, 183, 154, 85, -61,
    -93, 44, 95, 93, 82, 65, 10, -103,
    -302, -104, -58, -47, -46, -97, -131, -282
};

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

constexpr std::array<int, 7> PawnBonuses   = {0, 94, 202, 128, 60, 2, 8};
constexpr std::array<int, 7> PawnBonusesEG = {0, 85, 187, 111, 54, -1, 7};

constexpr uint64_t Msquares = 0x1818000000;

inline int PiecesValue(const int& PieceType){
    switch (PieceType){
        case 0: //PAWN
            return PAWN_VALUE_MG;
        case 1:
            return KNIGHT_VALUE_MG;
        case 2:
            return BISHOP_VALUE_MG;
        case 3:
            return ROOK_VALUE_MG;
        case 4:
            return QUEEN_VALUE_MG;
        default:
            return 0;

    }
}

int EvaluateKing(const chess::Square &KSq, const chess::Bitboard& occ, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite);
int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ, float weight, bool isWhite);
int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ ,const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite);
#endif