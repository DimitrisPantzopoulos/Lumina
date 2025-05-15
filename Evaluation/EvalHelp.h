#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -135, 8, -6, -154, -81, -76, -43, -166, -147, -20, 25, 93, 119, 0, -89, -157, -158, -39, 124, 213, 263, 95, -67, -178, -18, 53, 218, 204, 108, 63, 9, -63, 65, 181, 224, 210, 177, 159, 36, 86, 96, 45, 206, 564, 422, 202, -88, -29, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 76, 23, 96, 288, 271, 110, 34, 108, 83, 51, 64, 62, 39, 55, 93, 71, 96, 40, -4, -21, -66, -5, 53, 91, 121, 91, 8, 0, 60, 85, 92, 134, 296, 135, 11, 43, 26, 131, 232, 206, 751, 528, 578, 164, 266, 460, 902, 714, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {-351, -107, -96, -80, -56, 30, -112, -305, -88, -115, 25, 101, 92, 36, -48, -122, -48, 178, 226, 225, 203, 239, 95, -119, 147, 131, 265, 225, 170, 254, 141, 126, 365, 225, 448, 309, 280, 398, 201, 234, 252, 488, -106, 504, 487, -136, 488, 268, 103, -48, 477, -252, 167, 423, 171, 207, -22, -63, -557, -284, -225, -621, -166, -81};
constexpr int KnightPSTEg[] = {176, 125, 171, 168, 98, 95, 82, -14, 183, 246, 276, 275, 220, 299, 179, 241, 144, 269, 202, 380, 373, 200, 271, 189, 200, 328, 379, 431, 492, 390, 320, 141, 221, 407, 405, 457, 477, 483, 352, 186, 163, 133, 710, 379, 399, 665, 293, 261, 75, 377, 302, 649, 487, 326, 257, 152, -188, 256, 368, 466, 292, 317, 230, -301};       

constexpr int BishopPSTMg[] = {190, 247, 113, 94, 53, 100, 280, 70, 231, 380, 369, 267, 168, 302, 335, 378, 297, 268, 317, 273, 299, 251, 295, 242, 238, 232, 258, 326, 305, 320, 223, 166, 340, 274, 377, 427, 351, 259, 255, 271, 426, 319, -511, 198, 132, -555, 330, 366, 291, 79, 71, -664, -648, 120, 191, 156, 223, -414, -387, -708, -354, -722, -407, 155};
constexpr int BishopPSTEg[] = {91, 180, 152, 205, 188, 68, 9, 257, 139, 210, 267, 227, 313, 259, 204, 135, 234, 372, 310, 369, 377, 347, 347, 173, 229, 379, 409, 392, 445, 360, 328, 353, 208, 350, 361, 394, 459, 394, 351, 265, 233, 443, 655, 412, 504, 635, 377, 263, 46, 406, 463, 627, 634, 387, 344, 170, 190, 443, 473, 448, 337, 489, 599, 333};

constexpr int RookPSTMg[] = {-25, 4, 100, 170, 157, 29, 45, -18, -80, 76, -4, 73, 24, -24, -9, -97, -127, -19, 1, 87, 8, -62, 58, 20, 76, 87, -47, 58, 52, -72, -75, 37, 266, 163, 237, 242, 288, 59, 111, 142, 432, 386, 334, 301, 275, 217, 258, 349, 513, 252, 378, 345, 317, 326, 90, 252, 341, 35, -546, -653, -342, -226, 314, 372};
constexpr int RookPSTEg[] = {343, 460, 284, 369, 360, 416, 407, 357, 341, 358, 416, 410, 381, 460, 351, 345, 527, 477, 407, 405, 422, 487, 376, 361, 522, 466, 578, 517, 517, 532, 508, 481, 454, 512, 519, 558, 496, 648, 562, 567, 494, 505, 593, 592, 524, 624, 583, 478, 479, 636, 637, 650, 668, 655, 647, 575, 588, 667, 818, 903, 755, 717, 490, 552};       

constexpr int QueenPSTMg[] = {86, 9, 47, 260, 59, 25, 74, 76, 132, 205, 266, 122, 90, 248, 168, 184, 136, 195, 105, 84, 69, 36, 239, 186, 99, 160, 88, 96, 74, 117, 112, 137, 294, 99, 198, 228, 186, 179, 163, 108, 380, 494, 233, 252, 346, 395, 443, 338, 352, 289, 251, 208, 120, 239, 137, 440, 409, 247, 655, 219, 363, 616, 617, 290};
constexpr int QueenPSTEg[] = {924, 730, 570, -134, 830, 643, 642, 577, 633, 563, 615, 897, 961, 580, 773, 746, 835, 843, 1113, 1118, 1077, 1309, 727, 767, 970, 989, 1168, 1406, 1407, 1061, 1187, 969, 949, 1343, 1185, 1358, 1314, 1236, 1225, 1413, 817, 1014, 1240, 1217, 1124, 1168, 955, 840, 852, 960, 1277, 1301, 1444, 1179, 1207, 864, 773, 1031, 1032, 1241, 1224, 977, 938, 984};

constexpr int KingPSTMg[] = {114, 216, -9, -46, 33, -43, 257, 174, 6, -1, -98, -334, -382, -170, 43, 41, -376, -322, -455, -572, -477, -473, -205, -282, -589, -854, -741, -658, -647, -640, -533, -922, -166, -476, -674, -544, -577, -612, -518, -113, -28, -523, -181, 268, -96, -235, -832, -207, 276, -181, -351, -339, -62, 346, -383, 13, 25, -32, -12, -63, 98, 48, 110, 34};
constexpr int KingPSTEg[] = {-308, -305, -175, -210, -361, -152, -292, -363, -187, -75, -21, 74, 99, 4, -110, -186, -32, 49, 128, 179, 194, 131, 30, -63, 104, 243, 247, 327, 316, 258, 159, 135, 72, 257, 322, 289, 374, 304, 229, -1, 204, 455, 388, 367, 357, 389, 383, 35, -21, 361, 340, 382, 404, 297, 444, 27, -493, 144, 199, 304, 98, -85, -43, -476};     

constexpr int PawnBonusMg[] = {-48, -65, -73, 4, -33, 136, 130, 237};
constexpr int PawnBonusEg[] = {9, 100, 124, 133, 181, 139, 229, 41};

constexpr int DoubledPawnMg = -61;
constexpr int DoubledPawnEg = -107;

constexpr int IsolatedPawnMg = -105;
constexpr int IsolatedPawnEg = -68;

constexpr int PawnValueMg = 361;
constexpr int PawnValueEg = 464;

constexpr int KnightValueMg = 684;
constexpr int KnightValueEg = 1591;

constexpr int BishopValueMg = 865;
constexpr int BishopValueEg = 1614;

constexpr int RookValueMg = 1221;
constexpr int RookValueEg = 2702;

constexpr int QueenValueMg = 3411;
constexpr int QueenValueEg = 4267;

static constexpr uint64_t MIDDLE_SQUARES =  0x0000001818000000ULL;
static constexpr uint64_t NOT_HFILE      = ~0x8080808080808080ULL;
static constexpr uint64_t NOT_AFILE      = ~0x0101010101010101ULL;
static constexpr uint64_t RANK2          =  0x000000000000FF00ULL;

inline void FindPassedPawns(
    const chess::Bitboard& WhitePawns, 
    const chess::Bitboard& BlackPawns,

    chess::Bitboard& WhitePassedPawns,
    chess::Bitboard& BlackPassedPawns,

    int& WhiteScore,
    int& BlackScore,

    const int GamePhase
){  
    // PPE Algorithm, Simultaneously analyses pawns form both sides to determine if they are passed pawns Branchless and O(1).
    // Get Diagonals

    // Passed Pawn Detection
    // White
    const chess::Bitboard WDiagonalsNE = (WhitePawns & NOT_HFILE) << 9;
    const chess::Bitboard WDiagonalsNW = (WhitePawns & NOT_AFILE) << 7;

    // Black
    const chess::Bitboard BDiagonalsNE = (BlackPawns & NOT_AFILE) >> 9;
    const chess::Bitboard BDiagonalsNW = (BlackPawns & NOT_HFILE) >> 7;

    const chess::Bitboard WhitePawnsPassedPawnMask = NorthFill(WDiagonalsNE | WhitePawns | WDiagonalsNW);
    const chess::Bitboard BlackPawnsPassedPawnMask = SouthFill(BDiagonalsNE | BlackPawns | BDiagonalsNW);

    WhitePassedPawns = WhitePawns & ~BlackPawnsPassedPawnMask;
    BlackPassedPawns = BlackPawns & ~WhitePawnsPassedPawnMask;

    // Doubled Pawn Detection
    int DoubledPawnBonus = TaperedEval(DoubledPawnMg, DoubledPawnEg, GamePhase);

    WhiteScore += (SouthFill(WhitePawns >> 8) & WhitePawns).count() * DoubledPawnBonus;
    BlackScore += (NorthFill(BlackPawns << 8) & BlackPawns).count() * DoubledPawnBonus;

    // Isolated Pawn Detection
    chess::Bitboard WAdjacent = WDiagonalsNE | WDiagonalsNW;
    chess::Bitboard BAdjacent = BDiagonalsNE | BDiagonalsNW;

    chess::Bitboard WhiteAdjacentFileMasks = NorthFill(WAdjacent) | SouthFill(WAdjacent);
    chess::Bitboard BlackAdjacentFileMasks = NorthFill(BAdjacent) | SouthFill(BAdjacent);

    // Add the Isolated Pawns to the scores
    int IsolatedPawnBonus = TaperedEval(IsolatedPawnMg, IsolatedPawnEg, GamePhase);

    WhiteScore += (~WhiteAdjacentFileMasks & WhitePawns).count() * IsolatedPawnBonus;
    BlackScore += (~BlackAdjacentFileMasks & BlackPawns).count() * IsolatedPawnBonus;
}

inline void EvaluatePawns(
    const chess::Bitboard& WhitePawns,
    const chess::Bitboard& BlackPawns,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    int TaperedPawnValue = TaperedEval(PawnValueMg, PawnValueEg, GamePhase);

    WhiteScore += WhitePawns.count() * TaperedPawnValue;
    BlackScore += BlackPawns.count() * TaperedPawnValue;

    chess::Bitboard WhitePawnLocations = WhitePawns;
    chess::Bitboard BlackPawnLocations = BlackPawns;

    chess::Bitboard WhitePassedPawns;
    chess::Bitboard BlackPassedPawns;

    chess::Bitboard WhiteIsolatedPawns;
    chess::Bitboard BlackIsolatedPawns;

    chess::Bitboard WhiteDoubledPawns;
    chess::Bitboard BlackDoubledPawns;

    FindPassedPawns(WhitePawns, BlackPawns, WhitePassedPawns, BlackPassedPawns, WhiteScore, BlackScore, GamePhase);

    // Add the Isolated Pawns to the scores
    int IsolatedPawnBonus = TaperedEval(IsolatedPawnMg, IsolatedPawnEg, GamePhase);

    WhiteScore += WhiteIsolatedPawns.count() * IsolatedPawnBonus;
    BlackScore += BlackIsolatedPawns.count() * IsolatedPawnBonus;

    while(WhitePawnLocations != 0){
        uint8_t  Index    = WhitePawnLocations.pop();
        WhiteScore += TaperedEval(PawnPSTMg[Index], PawnPSTEg[Index], GamePhase);
    }

    while(BlackPawnLocations != 0){
        uint8_t Index = 63 - BlackPawnLocations.pop();
        BlackScore += TaperedEval(PawnPSTMg[Index], PawnPSTEg[Index], GamePhase);
    }

    // Passed Pawns are worth more if they are higher up the board
    for(int i=0;i<8;i++){
        uint64_t RankBitboard = RANK2 << (8 * i);

        WhiteScore += (RankBitboard & WhitePassedPawns).count() * TaperedEval(PawnBonusMg[i],   PawnBonusMg[i],   GamePhase);
        BlackScore += (RankBitboard & BlackPassedPawns).count() * TaperedEval(PawnBonusMg[7-i], PawnBonusMg[7-i], GamePhase);
    }
}

inline void EvaluateKnights(
    const chess::Bitboard& WhiteKnights,
    const chess::Bitboard& BlackKnights,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    int TaperedKnightValue = TaperedEval(KnightValueMg, KnightValueEg, GamePhase);

    WhiteScore += WhiteKnights.count() * TaperedKnightValue;
    BlackScore += BlackKnights.count() * TaperedKnightValue;

    chess::Bitboard WhiteKnightLocations = WhiteKnights;
    chess::Bitboard BlackKnightLocations = BlackKnights;

    while(WhiteKnightLocations != 0){
        uint8_t Index = WhiteKnightLocations.pop();
        WhiteScore += TaperedEval(KnightPSTMg[Index], KnightPSTEg[Index], GamePhase);
    }

    while(BlackKnightLocations != 0){
        uint8_t Index = 63 - BlackKnightLocations.pop();
        BlackScore += TaperedEval(KnightPSTMg[Index], KnightPSTEg[Index], GamePhase);
    }
}

inline void EvaluateBishops(
    const chess::Bitboard& WhiteBishops,
    const chess::Bitboard& BlackBishops,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    int TaperedBishopValue = TaperedEval(BishopValueMg, BishopValueEg, GamePhase);

    WhiteScore += WhiteBishops.count() * TaperedBishopValue;
    BlackScore += BlackBishops.count() * TaperedBishopValue;

    chess::Bitboard WhiteBishopLocations = WhiteBishops;
    chess::Bitboard BlackBishopLocations = BlackBishops;

    while(WhiteBishopLocations != 0){
        uint8_t Index = WhiteBishopLocations.pop();
        WhiteScore += TaperedEval(BishopPSTMg[Index], BishopPSTEg[Index], GamePhase);
    }

    while(BlackBishopLocations != 0){
        uint8_t Index = 63 - BlackBishopLocations.pop();
        BlackScore += TaperedEval(BishopPSTMg[Index], BishopPSTEg[Index], GamePhase);
    }
}

inline void EvaluateRooks(
    const chess::Bitboard& WhiteRooks,
    const chess::Bitboard& BlackRooks,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    int TaperedRookValue = TaperedEval(RookValueMg, RookValueEg, GamePhase);

    WhiteScore += WhiteRooks.count() * TaperedRookValue;
    BlackScore += BlackRooks.count() * TaperedRookValue;

    chess::Bitboard WhiteRookLocations = WhiteRooks;
    chess::Bitboard BlackRookLocations = BlackRooks;

    while (WhiteRookLocations != 0) {
        uint8_t Index = WhiteRookLocations.pop();
        WhiteScore += TaperedEval(RookPSTMg[Index], RookPSTEg[Index], GamePhase);
    }

    while (BlackRookLocations != 0) {
        uint8_t Index = 63 - BlackRookLocations.pop();
        BlackScore += TaperedEval(RookPSTMg[Index], RookPSTEg[Index], GamePhase);
    }
}

inline void EvaluateQueens(
    const chess::Bitboard& WhiteQueens,
    const chess::Bitboard& BlackQueens,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    int TaperedQueenValue = TaperedEval(QueenValueMg, QueenValueEg, GamePhase);

    WhiteScore += WhiteQueens.count() * TaperedQueenValue;
    BlackScore += BlackQueens.count() * TaperedQueenValue;

    chess::Bitboard WhiteQueenLocations = WhiteQueens;
    chess::Bitboard BlackQueenLocations = BlackQueens;

    while (WhiteQueenLocations != 0) {
        uint8_t Index = WhiteQueenLocations.pop();
        WhiteScore += TaperedEval(QueenPSTMg[Index], QueenPSTEg[Index], GamePhase);
    }

    while (BlackQueenLocations != 0) {
        uint8_t Index = 63 - BlackQueenLocations.pop();
        BlackScore += TaperedEval(QueenPSTMg[Index], QueenPSTEg[Index], GamePhase);
    }
}

inline void EvaluateKings(
    const chess::Bitboard& WhiteKing,
    const chess::Bitboard& BlackKing,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    uint8_t WhiteIndex = WhiteKing.lsb();
    WhiteScore += TaperedEval(KingPSTMg[WhiteIndex], KingPSTEg[WhiteIndex], GamePhase);

    uint8_t BlackIndex = 63 - BlackKing.lsb();
    BlackScore += TaperedEval(KingPSTMg[BlackIndex], KingPSTEg[BlackIndex], GamePhase);
}

inline int PiecesValue(const int& PieceType){
    switch (PieceType){
        case 0: //PAWN
            return PawnValueMg;
        case 1:
            return KnightValueMg;
        case 2:
            return BishopValueMg;
        case 3:
            return RookValueMg;
        case 4:
            return QueenValueMg;
        default:
            return 0;
    }
}

#endif