#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess-library\include\chess.hpp"
<<<<<<< Updated upstream

int PiecesValueEval(const int& PieceType, float weight);
int SafetyScore(const chess::Square &KSq,const chess::Bitboard& occ, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite);
int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ, float weight, bool isWhite);
int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ ,const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite);
int EvaluateQueen(const chess::Square &sq, const chess::Board& board, const chess::Bitboard& EnemyPawns, const chess::Bitboard occ, const chess::Color EnemyColor, float weight);
=======
#include "..\Helper\HelperFunctions.h"

constexpr double mg_pawn_table[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    42.6171, 119.664, 60.7776, 12.6068, 33.5447, 64.1162, 49.143, -11.3411,
    -56.3674, -14.545, 23.0876, 94.1974, 130.819, 48.4872, -7.76344, -48.9271,
    -62.4375, -28.0658, 65.0316, 62.0502, 92.8741, 71.0988, -31.7919, -62.6107,
    7.96825, 42.2553, 71.7615, 52.2688, 2.09334, 21.3148, 19.18, 8.85811,
    31.8804, 55.636, -11.8463, 25.1362, 23.2642, 63.306, 48.0157, 66.6379,
    61.403, 90.2374, 138.587, 11.3739, 11.8602, 27.2056, 180.395, 39.7595,
    0, 0, 0, 0, 0, 0, 0, 0
};
constexpr double eg_pawn_table[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    122.617, 158.664, 157.778, 51.6068, 112.545, 70.1162, 180.143, 186.659,
    43.6326, 78.455, 82.0876, 130.197, 121.819, 45.4872, 49.2366, 55.0729,
    -16.4375, -17.0658, 72.0316, 46.0502, 67.8741, 63.0988, -31.7919, -22.6107,
    47.9683, 53.2553, 73.7615, 33.2688, -21.9067, 7.31476, 12.18, 32.8581,
    61.8804, 66.636, -13.8463, 36.1362, 20.2642, 55.306, 14.0157, 70.6379,
    109.403, 99.2374, 166.587, 44.3739, 39.8602, 3.20562, 144.395, 54.7595,
    0, 0, 0, 0, 0, 0, 0, 0
};
constexpr double mg_knight_table[64] = {
    -524.281, -248.161, -150.812, -132.73, -107.32, -32.9033, -274.334, -616.322,
    -165.401, -96.8446, -35.9356, 74.5167, 53.4012, -19.9225, -80.3586, -201.386,
    -187.509, 149.433, 224.204, 321.059, 282.951, 246.826, 58.4683, -284.285,
    73.7155, 156.206, 343.862, 285.083, 251.775, 348.577, 104.06, 40.9289,
    237.136, 254.943, 463.078, 374.327, 353.288, 473.554, 236.26, 214.827,
    38.4348, 309.232, 280.285, 545.709, 511.331, 233.931, 453.311, 204.097,
    -57.902, 43.9045, 467.664, 214.732, 307.078, 538.419, 128.83, 51.8775,
    -352.776, -71.7861, -236.616, -196.638, 43.8713, -53.7993, -72.3938, -465.891
};
constexpr double mg_bishop_table[64] = {
    89.9954, 174.379, 51.5737, -4.62051, -29.8913, 41.7295, 153.464, 155.957,
    188.939, 283.102, 263.537, 139.374, 27.4484, 112.736, 254.159, 333.455,
    201.056, 184.154, 169.72, 51.2717, 82.9763, 89.8643, 173.685, 140.291,
    236.895, 50.9367, 11.9001, 61.6539, 98.1009, 67.9629, 16.1623, 116.936,
    233.636, 156.178, 83.3189, 181.656, 86.4178, -21.1776, 99.0373, 153.746,
    261.713, 265.465, -808.874, -12.6369, 24.001, -764.604, 215.553, 201.251,
    73.732, 53.561, -31.1994, -283.212, -449.115, -40.4352, 38.7029, 29.8214,
    158.383, 76.5003, -29.1789, 69.097, -113.29, -95.7641, 198.682, 38.0318
};
constexpr double mg_rook_table[64] = {
    -33.4339, 15.5078, 105.495, 121.574, 105.833, 38.6325, 52.4646, -15.3852,
    -78.7479, 137.564, 15.7089, 50.9498, 10.2172, 18.1257, -10.8157, -128.69,
    50.3985, 85.739, 10.5451, 41.1537, 1.60691, 12.7445, 79.823, 71.1851,
    134.569, 123.793, 107.526, 90.1413, 71.8209, 79.8043, 28.6523, 110.144,
    253.006, 251.494, 215.516, 233.744, 178.144, 216.072, 251.634, 283.695,
    349.631, 372.5, 317.27, 294.69, 185.982, 242.098, 327.837, 308.002,
    17.0939, 25.5996, 121.39, 126.316, 57.5008, 19.8538, -44.9338, 31.0049,
    299.423, 315.851, 268.202, 205.029, 138.727, 168.474, 229.324, 401.692
};
constexpr double mg_queen_table[64] = {
    250.066, 121.821, 126.071, 396.6, 129.467, 77.9873, 155.771, 177.165,
    211.726, 276.715, 401.756, 271.286, 239.154, 362.142, 331.423, 300.865,
    292.62, 323.734, 341.894, 306.735, 311.847, 252.6, 404.923, 289.163,
    204.106, 339.221, 338.674, 363.026, 331.802, 386.05, 355.986, 305.824,
    539.312, 382.872, 459.56, 611.019, 510.167, 443.845, 454.723, 372.433,
    457.454, 776.983, 533.479, 599.121, 611.721, 785.639, 617.494, 503.336,
    409.995, 528.024, 582.231, 629.637, 554.471, 567.814, 449.169, 528.377,
    432.483, 554.7, 648.875, 607.849, 716.326, 694.126, 684.704, 433.35
};
constexpr double mg_king_table[64] = {
    -39.8096, 42.3242, -23.622, -96.8612, -54.3536, -54.6707, 20.9817, -39.8663,
    -41.5014, -7.15859, -0.104041, 8.02462, -13.3414, -11.7276, -9.92201, -50.0209,
    -70.4229, 42.4266, 77.723, 75.8827, 101.346, 49.1156, 10.8442, -59.0108,
    -3.27885, 70.3671, 146.556, 176.817, 168.367, 152.446, 51.0186, -60.7343,
    40.3858, 143.805, 187.994, 183.504, 246.007, 145.89, 110.535, 30.5605,
    121.908, 272.505, 291.868, 256.229, 275.887, 254.826, 171.5, -17.5949,
    5.56634, 248.21, 223.949, 172.43, 308.155, 224.653, 215.493, 65.5888,
    -199.28, 182.791, 122.328, 193.356, 253.21, 23.3903, 148.573, -128.774
};
constexpr double eg_king_table[64] = {
    -48.8096, -15.6758, -57.622, -99.8612, -9.35358, -5.6707, 22.9817, -69.8663,
    -82.5014, 10.8414, 33.896, 32.0246, 11.6586, 30.2724, 51.078, -10.0209,
    -51.4229, 35.4266, 98.723, 106.883, 141.346, 88.1156, 32.8442, -24.0108,
    5.72115, 112.367, 182.556, 230.817, 224.367, 210.446, 91.0186, -21.7343,
    71.3858, 140.805, 235.994, 246.504, 319.007, 212.89, 152.535, 70.5605,
    116.908, 283.505, 324.868, 323.229, 342.887, 300.826, 193.5, 0.405115,
    -22.4337, 230.21, 235.949, 249.43, 365.155, 244.653, 201.493, 40.5888,
    -237.28, 112.791, 89.328, 236.356, 217.21, 37.3903, 100.573, -185.774
};
constexpr double PawnBonuses[8] = {
    0, -32.0603, 38.288, 77.8798, 76.2642, 147.138, 305.45, 0
};
constexpr double PawnBonusesEG[8] = {
    0, -27.0603, 43.288, 82.8798, 81.2642, 157.138, 325.45, 0
};
constexpr double PAWN_VALUE_MG = 229.116;
constexpr double PAWN_VALUE_EG = 229.116;
constexpr double KNIGHT_VALUE_MG = 909.738;
constexpr double KNIGHT_VALUE_EG = 899.738;
constexpr double BISHOP_VALUE_MG = 859.653;
constexpr double BISHOP_VALUE_EG = 854.653;
constexpr double ROOK_VALUE_MG = 1463.18;
constexpr double ROOK_VALUE_EG = 1473.18;
constexpr double QUEEN_VALUE_MG = 3091.2;
constexpr double QUEEN_VALUE_EG = 3121.2;
constexpr double PASSEDPAWN_MG = 27.387;
constexpr double PASSEDPAWN_EG = 57.387;
constexpr double DOUBLEDPAWN_MG = -66.5082;
constexpr double DOUBLEDPAWN_EG = -61.5082;
constexpr double ISOLATEDPAWN_MG = -69.2533;
constexpr double ISOLATEDPAWN_EG = -64.2533;
constexpr double CENTREPAWN_MG = 64.6961;
constexpr double CENTREPAWN_EG = 62.6961;
constexpr double NONFIXEDPAWN_MG = -17.9578;
constexpr double NONFIXEDPAWN_EG = -7.95783;
constexpr double KNIGHTOUTPOST_MG = 74.0902;
constexpr double KNIGHTOUTPOST_EG = 64.0902;
constexpr double KNIGHTMOBILITY_MG = 0.695775;
constexpr double KNIGHTMOBILITY_EG = -0.304225;
constexpr double BISHOPMOBILITY_MG = 29.9627;
constexpr double BISHOPMOBILITY_EG = 28.9627;
constexpr double ROOKMOBILITY_MG = 13.3743;
constexpr double ROOKMOBILITY_EG = 13.3743;
constexpr double ROOKOPENFILE_MG = 61.6251;
constexpr double ROOKOPENFILE_EG = 66.6251;
constexpr double ROOKBACKRANK_MG = 150.162;
constexpr double ROOKBACKRANK_EG = 148.162;
constexpr double BISHOPOPENFILE_MG = 7.50303;
constexpr double BISHOPOPENFILE_EG = 7.50303;
constexpr double TWOBISHOPS_MG = 168.641;
constexpr double TWOBISHOPS_EG = 178.641;
constexpr double BISHOPFIXEDPAWNS_MG = -27.8397;
constexpr double BISHOPFIXEDPAWNS_EG = -25.8397;
constexpr double NOPAWNSHIELD_MG = 34.4031;
constexpr double NOPAWNSHIELD_EG = 44.4031;
constexpr double VQUEENSCOREMG = -15.7765;
constexpr double VQUEENSCOREEG = -10.7765;

// END OF PSTS
inline int PiecesValue(const int& PieceType){
    constexpr int PAWN_VALUE_MG = 241;
    constexpr int PAWN_VALUE_EG = 241;
    constexpr int KNIGHT_VALUE_MG = 907;
    constexpr int KNIGHT_VALUE_EG = 897;
    constexpr int BISHOP_VALUE_MG = 858;
    constexpr int BISHOP_VALUE_EG = 853;
    constexpr int ROOK_VALUE_MG = 1470;
    constexpr int ROOK_VALUE_EG = 1480;
    constexpr int QUEEN_VALUE_MG = 3079;
    constexpr int QUEEN_VALUE_EG = 3109;

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

// Structural Evaluations
void EvaluatePawns(
    const chess::Bitboard& WhitePawns, 
    const chess::Bitboard& BlackPawns,
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight
);

void EvaluateBishops(
    const chess::Bitboard& WhiteBishops,             const chess::Bitboard& BlackBishops,
    const chess::Bitboard& WhitePawns,               const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares,  const chess::Bitboard& BlackPawnsAttackSquares,
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight
);

void EvaluateKnights(
    const chess::Bitboard& WhiteKnights,             const chess::Bitboard& BlackKnights,
    const chess::Bitboard& WhitePawns,               const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares,  const chess::Bitboard& BlackPawnsAttackSquares,
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight
);

void EvaluateRooks(
    const chess::Bitboard& WhiteRooks,               const chess::Bitboard& BlackRooks,
    const chess::Bitboard& WhitePawns,               const chess::Bitboard& BlackPawns,
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight
);

// Positional Evaluations
inline double EvaluatePawn(
    const chess::Square& Sq,
    const float EndgameWeight,
    const bool Color,
    int PSTIndex
)
{   
    int Rank = Sq.rank();
    Rank = Color ? Rank : (7 - Rank);
    int SquareIndex = PSTIndex;
    
    // Pawn Bonuses + Pawn Value + Pawn PST
    return TaperedEvaluation(EndgameWeight, PawnBonuses[Rank], PawnBonusesEG[Rank]) +
           TaperedEvaluation(EndgameWeight, PAWN_VALUE_MG, PAWN_VALUE_EG)           +
           TaperedEvaluation(EndgameWeight, mg_pawn_table[SquareIndex], eg_pawn_table[SquareIndex]);
}

inline double EvaluateKnight(
    const chess::Square&   Sq,
    const chess::Bitboard& EnemyPawnThreats,
    const float weight,
    const int PSTIndex
)
{   
    // Evaluate Knight Mobility disregarding the squares which are attacked by enemy pawns + Knight PST + Knight Value
    return (chess::attacks::knight(Sq) & ~EnemyPawnThreats).count() * TaperedEvaluation(weight, KNIGHTMOBILITY_MG, KNIGHTMOBILITY_EG) + 
            mg_knight_table[PSTIndex] +
            TaperedEvaluation(weight, KNIGHT_VALUE_MG, KNIGHT_VALUE_EG);
}

inline double EvaluateBishop(
    const chess::Square &Sq, 
    const chess::Bitboard& occ,
    const chess::Bitboard& EnemyPawns,
    const uint64_t HalfTest,
    const float weight,
    const int PSTIndex
)
{
    return chess::attacks::bishop(Sq, occ).count() * TaperedEvaluation(weight, BISHOPMOBILITY_MG, BISHOPMOBILITY_EG) +
           mg_bishop_table[PSTIndex] +
           TaperedEvaluation(weight, BISHOP_VALUE_MG, BISHOP_VALUE_EG) +
           (chess::attacks::bishop(Sq, EnemyPawns) & HalfTest).count() * TaperedEvaluation(weight, BISHOPOPENFILE_MG, BISHOPOPENFILE_EG);
}

inline double EvaluateRook(
    const chess::Square &Sq, 
    const chess::Bitboard& occ, 
    const float weight,
    const int PSTIndex
)
{   
    // Rook Mobility + Mobility + Rook PST
    return chess::attacks::rook(Sq, occ).count() * TaperedEvaluation(weight, ROOKMOBILITY_MG, ROOKMOBILITY_EG) +
           mg_rook_table[PSTIndex] +
           TaperedEvaluation(weight, ROOK_VALUE_MG, ROOK_VALUE_EG);
}

inline double EvaluateQueen(
    const chess::Square &Sq,
    const chess::Bitboard& occ,
    const float weight,
    const int PSTIndex
)
{
    // Queen Value + Queen PST
    constexpr uint64_t MIDDLE_SQUARES = 0x1818000000ULL;

    // Count mobility
    chess::Bitboard QueenMobility = chess::attacks::queen(Sq, occ);

    // Pressure on Middle Square
    return mg_queen_table[PSTIndex] +
        TaperedEvaluation(weight, QUEEN_VALUE_MG, QUEEN_VALUE_EG);
        //(QueenMobility & MIDDLE_SQUARES).count() * TaperedEvaluation(weight, QUEENMIDDLESQUAREPRESSURE_MG, QUEENMIDDLESQUAREPRESSURE_EG);
}

inline double EvaluateKing(
    const chess::Square &Sq,
    const chess::Bitboard& FriendlyPawns,
    const chess::Bitboard& occ,
    const int PSTIndex,
    const float weight,
    const bool Color
)
{
    int Score = TaperedEvaluation(weight, mg_king_table[PSTIndex], eg_king_table[PSTIndex]);

    Score += chess::attacks::queen(Sq, occ).count() * TaperedEvaluation(weight, VQUEENSCOREMG, VQUEENSCOREEG);

    int File = Sq.file();

    uint64_t KingMaskIndex = 1ULL << Sq.index();
    uint64_t KingForwardMask = Color ? NorthFill(KingMaskIndex) : SouthFill(KingMaskIndex);
    uint64_t LeftMask    = File != 0 ? KingForwardMask << 1 : 0ULL;
    uint64_t RightMask   = File != 7 ? KingForwardMask >> 1 : 0ULL;
    uint64_t CombinedMask = LeftMask | KingForwardMask | RightMask;

    Score += (FriendlyPawns & CombinedMask).count() * TaperedEvaluation(weight, NOPAWNSHIELD_MG, NOPAWNSHIELD_EG);

    return Score;
}

>>>>>>> Stashed changes
#endif