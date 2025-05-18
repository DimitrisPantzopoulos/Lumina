#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -34, 8, 25, 6, 61, 57, 104, 2, -27, 7, 57, 75, 111, 88, 129, 76, -20, 20, 71, 133, 130, 112, 71, 47, 16, 55, 97, 126, 188, 153, 121, 84, 70, 87, 206, 252, 264, 337, 246, 118, 363, 432, 351, 445, 415, 380, 135, 43, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 162, 141, 136, 130, 161, 125, 90, 111, 138, 126, 98, 96, 93, 94, 74, 79, 157, 137, 100, 71, 69, 83, 99, 92, 234, 188, 143, 87, 80, 102, 145, 153, 442, 452, 339, 244, 218, 223, 355, 358, 672, 627, 639, 478, 452, 481, 636, 677, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {120, 192, 51, 102, 122, 133, 201, 224, 166, 110, -31, 23, 20, 9, 175, 281, 111, -11, -156, -123, -85, -124, 71, 177, 176, 20, -105, -96, -70, -80, 98, 220, 224, 74, -46, 36, -33, 54, 108, 336, 223, 157, 25, 56, 208, 207, 251, 338, 304, 240, 133, 195, 140, 372, 257, 421, -35, -47, 49, 184, 288, 203, 83, 160};
constexpr int KnightPSTEg[] = {387, 244, 220, 219, 206, 184, 261, 380, 266, 208, 57, 61, 62, 34, 186, 319, 231, 72, -101, -75, -87, -133, 47, 226, 273, 93, -44, -51, -36, -77, 95, 249, 260, 126, -50, -41, -28, -52, 127, 238, 243, 83, -89, -79, -126, -144, 46, 201, 303, 262, 71, 69, 46, 2, 252, 242, 264, 320, 266, 227, 237, 158, 315, 182};

constexpr int BishopPSTMg[] = {255, 301, 239, 193, 215, 210, 243, 307, 296, 279, 294, 222, 251, 262, 334, 301, 269, 279, 254, 238, 244, 241, 282, 321, 243, 234, 230, 292, 271, 227, 220, 262, 252, 250, 300, 
344, 319, 301, 249, 253, 287, 327, 323, 375, 370, 505, 391, 380, 292, 301, 260, 216, 325, 378, 313, 328, 232, 179, 170, 22, 134, 252, 255, 176};
constexpr int BishopPSTEg[] = {253, 292, 241, 282, 271, 289, 251, 194, 312, 272, 242, 285, 288, 243, 264, 250, 311, 297, 285, 285, 295, 275, 271, 272, 296, 298, 300, 264, 249, 281, 296, 278, 313, 314, 270, 
265, 251, 274, 307, 306, 327, 291, 278, 240, 246, 258, 270, 321, 258, 271, 284, 283, 239, 241, 286, 238, 282, 315, 299, 351, 314, 272, 268, 271};

constexpr int RookPSTMg[] = {422, 430, 457, 463, 469, 412, 484, 429, 357, 406, 463, 451, 468, 454, 517, 409, 371, 405, 407, 443, 457, 444, 557, 482, 391, 402, 433, 477, 473, 441, 509, 478, 464, 498, 511, 551, 554, 566, 603, 579, 510, 576, 574, 603, 721, 692, 829, 716, 583, 575, 628, 715, 644, 804, 739, 801, 654, 609, 671, 682, 711, 744, 689, 727};
constexpr int RookPSTEg[] = {817, 841, 861, 851, 825, 808, 816, 792, 823, 827, 828, 832, 798, 786, 765, 789, 849, 846, 831, 838, 815, 793, 747, 761, 869, 876, 877, 847, 848, 843, 807, 800, 885, 881, 902, 885, 839, 824, 811, 803, 888, 896, 897, 882, 841, 827, 803, 791, 894, 935, 945, 910, 914, 858, 852, 816, 887, 917, 935, 926, 902, 870, 880, 869};

constexpr int QueenPSTMg[] = {1148, 1137, 1158, 1203, 1187, 1097, 1183, 1165, 1181, 1202, 1242, 1242, 1235, 1243, 1261, 1303, 1188, 1218, 1186, 1215, 1215, 1224, 1276, 1255, 1198, 1183, 1198, 1200, 1211, 1223, 1242, 1258, 1177, 1209, 1213, 1228, 1216, 1266, 1281, 1285, 1236, 1240, 1222, 1268, 1341, 1439, 1508, 1436, 1241, 1165, 1200, 1156, 1172, 1353, 1304, 1450, 1142, 1155, 1262, 1349, 1358, 1391, 1421, 1247};
constexpr int QueenPSTEg[] = {1426, 1440, 1451, 1466, 1403, 1420, 1329, 1362, 1441, 1449, 1459, 1487, 1506, 1390, 1317, 1269, 1459, 1527, 1582, 1575, 1578, 1544, 1507, 1480, 1498, 1605, 1620, 1682, 1686, 1651, 1616, 1582, 1547, 1606, 1648, 1718, 1771, 1718, 1681, 1619, 1537, 1577, 1725, 1709, 1730, 1670, 1548, 1535, 1517, 1651, 1710, 1770, 1823, 1691, 1640, 1558, 1584, 1623, 1659, 1635, 1638, 1585, 1481, 1571};

constexpr int KingPSTMg[] = {97, 172, 135, -111, 90, -82, 139, 143, 155, 69, 62, -38, -38, -31, 119, 87, -59, 22, -141, -166, -179, -179, -54, -145, -165, -158, -234, -312, -315, -218, -259, -389, -140, -164, -159, -296, -268, -203, -231, -330, -250, 69, -127, -124, -31, 143, 68, -64, -206, -60, -166, 11, -67, -19, 112, 35, -77, -89, -56, -195, -124, -27, 43, 66};
constexpr int KingPSTEg[] = {-225, -153, -84, -41, -117, -43, -127, -250, -140, -22, 22, 58, 67, 49, -32, -116, -78, 25, 113, 155, 158, 128, 44, -27, -53, 76, 178, 237, 236, 179, 117, 36, -23, 119, 194, 253, 255, 226, 169, 69, 11, 105, 187, 218, 223, 202, 175, 55, -42, 79, 124, 107, 154, 185, 136, 16, -289, -131, -81, 21, -10, 1, -21, -287};

constexpr int PawnBonusMg[] = {27, -7, -19, 19, -7, 36, 24, -60};
constexpr int PawnBonusEg[] = {44, 70, 92, 113, 132, 144, 169, 150};

constexpr int DoubledPawnMg = -11;
constexpr int DoubledPawnEg = -62;

constexpr int IsolatedPawnBonusMg = -57;
constexpr int IsolatedPawnBonusEg = -44;

constexpr int PawnValueMg = 168;
constexpr int PawnValueEg = 224;

constexpr int KnightValueMg = 372;
constexpr int KnightValueEg = 392;

constexpr int BishopValueMg = 680;
constexpr int BishopValueEg = 709;

constexpr int RookValueMg = 810;
constexpr int RookValueEg = 1138;

constexpr int QueenValueMg = 1686;
constexpr int QueenValueEg = 2049;

constexpr int VirtualQueenMg = -19;
constexpr int VirtualQueenEg = -5;

constexpr int PawnShieldMg = 59;
constexpr int PawnShieldEg = -27;

constexpr int KnightMobilityMg = 101;
constexpr int KnightMobilityEg = 107;

constexpr int BishopMobilityMg = 27;
constexpr int BishopMobilityEg = 24;

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
    int IsolatedPawnBonus = TaperedEval(IsolatedPawnBonusMg, IsolatedPawnBonusEg, GamePhase);

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

    FindPassedPawns(WhitePawns, BlackPawns, WhitePassedPawns, BlackPassedPawns, WhiteScore, BlackScore, GamePhase);

    while(WhitePawnLocations != 0){
        uint8_t  Index    = WhitePawnLocations.pop();
        WhiteScore += TaperedEval(PawnPSTMg[Index], PawnPSTEg[Index], GamePhase);
    }

    while(BlackPawnLocations != 0){
        uint8_t Index = MirrorSquare(BlackPawnLocations.pop());
        BlackScore += TaperedEval(PawnPSTMg[Index], PawnPSTEg[Index], GamePhase);
    }

    // Passed Pawns are worth more if they are higher up the board
    for(int i=0;i<6;i++){
        uint64_t RankBitboard = RANK2 << (8 * i);

        WhiteScore += (RankBitboard & WhitePassedPawns).count() * TaperedEval(PawnBonusMg[i],   PawnBonusEg[i],   GamePhase);
        BlackScore += (RankBitboard & BlackPassedPawns).count() * TaperedEval(PawnBonusMg[7-i], PawnBonusEg[7-i], GamePhase);
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

    int KnightMobilityBonus = TaperedEval(KnightMobilityMg, KnightMobilityEg, GamePhase);

    while(WhiteKnightLocations != 0){
        const uint8_t Index = WhiteKnightLocations.pop();
        const chess::Bitboard KnightMoves = chess::attacks::knight(Index);

        // PST + Mobility
        WhiteScore += KnightMoves.count() * KnightMobilityBonus;
        WhiteScore += TaperedEval(KnightPSTMg[Index], KnightPSTEg[Index], GamePhase);
    }

    while(BlackKnightLocations != 0){
        const uint8_t RawIndex = BlackKnightLocations.pop();
        const uint8_t PSTIndex = MirrorSquare(RawIndex);
        
        const chess::Bitboard KnightMoves = chess::attacks::knight(RawIndex);

        // PST + Mobility
        BlackScore += KnightMoves.count() * KnightMobilityBonus;
        BlackScore += TaperedEval(KnightPSTMg[PSTIndex], KnightPSTEg[PSTIndex], GamePhase);
    }
}

inline void EvaluateBishops(
    const chess::Bitboard& WhiteBishops,
    const chess::Bitboard& BlackBishops,
    const chess::Bitboard& OCC,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    const int TaperedBishopValue = TaperedEval(BishopValueMg, BishopValueEg, GamePhase);

    WhiteScore += WhiteBishops.count() * TaperedBishopValue;
    BlackScore += BlackBishops.count() * TaperedBishopValue;

    chess::Bitboard WhiteBishopLocations = WhiteBishops;
    chess::Bitboard BlackBishopLocations = BlackBishops;

    const int BishopMobilityBonus = TaperedEval(BishopMobilityMg, BishopMobilityEg, GamePhase);

    while(WhiteBishopLocations != 0){
        const uint8_t Index = WhiteBishopLocations.pop();
        const chess::Bitboard BishopMoves = chess::attacks::bishop(Index, OCC);
        
        WhiteScore += BishopMoves.count() * BishopMobilityBonus;
        WhiteScore += TaperedEval(BishopPSTMg[Index], BishopPSTEg[Index], GamePhase);
    }

    while(BlackBishopLocations != 0){
        const uint8_t Index    = BlackBishopLocations.pop();
        const uint8_t PSTIndex = MirrorSquare(Index);
        const chess::Bitboard BishopMoves = chess::attacks::bishop(Index, OCC);

        BlackScore += BishopMoves.count() * BishopMobilityBonus;
        BlackScore += TaperedEval(BishopPSTMg[PSTIndex], BishopPSTEg[PSTIndex], GamePhase);
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
        uint8_t Index = MirrorSquare(BlackRookLocations.pop());
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
        uint8_t Index = MirrorSquare(BlackQueenLocations.pop());
        BlackScore += TaperedEval(QueenPSTMg[Index], QueenPSTEg[Index], GamePhase);
    }
}

inline void EvaluateKings(
    const chess::Bitboard& WhiteKing,
    const chess::Bitboard& BlackKing,

    const chess::Bitboard& WhitePawns,
    const chess::Bitboard& BlackPawns,

    const chess::Bitboard& OCC,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    chess::Square WhiteKingSquare(WhiteKing.lsb());
    chess::Square BlackKingSquare(BlackKing.lsb());

    int WhiteKingPSTIndex = WhiteKingSquare.index();
    int BlackKingPSTIndex = MirrorSquare(BlackKingSquare.index());

    WhiteScore += TaperedEval(KingPSTMg[WhiteKingPSTIndex],  KingPSTEg[WhiteKingPSTIndex], GamePhase);
    BlackScore += TaperedEval(KingPSTMg[BlackKingPSTIndex],  KingPSTEg[BlackKingPSTIndex], GamePhase);

    // Virtual Queen Score
    int VirtualQueenBonus = TaperedEval(VirtualQueenMg, VirtualQueenEg, GamePhase);

    WhiteScore += chess::attacks::queen(WhiteKingSquare, OCC).count() * VirtualQueenBonus;
    BlackScore += chess::attacks::queen(BlackKingSquare, OCC).count() * VirtualQueenBonus;

    // Evaluate Pawn Shield
    int PawnShieldBonus = TaperedEval(PawnShieldMg, PawnShieldEg, GamePhase);

    // Pawn Shield Evaluation
    const chess::Bitboard WhiteKingForwardsMask = ((WhiteKing & NOT_HFILE) << 9) | (WhiteKing << 8) | ((WhiteKing & NOT_AFILE) << 7);
    const chess::Bitboard BlackKingForwardsMask = ((BlackKing & NOT_AFILE) >> 9) | (BlackKing >> 8) | ((BlackKing & NOT_HFILE) >> 7);

    WhiteScore += (WhiteKingForwardsMask & WhitePawns).count() * PawnShieldBonus;
    BlackScore += (BlackKingForwardsMask & BlackPawns).count() * PawnShieldBonus;
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