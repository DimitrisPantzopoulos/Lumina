#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -33, 7, 21, 3, 56, 57, 105, 2, -24, 7, 53, 69, 106, 87, 130, 76, -19, 22, 69, 132, 129, 112, 72, 48, 20, 57, 98, 126, 191, 156, 119, 87, 79, 91, 213, 259, 275, 346, 243, 127, 373, 434, 348, 446, 411, 377, 139, 49, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 162, 140, 133, 120, 154, 124, 89, 110, 139, 125, 97, 94, 92, 93, 74, 81, 159, 138, 99, 70, 69, 83, 99, 95, 236, 189, 143, 89, 80, 
102, 146, 155, 442, 454, 341, 248, 220, 223, 360, 361, 673, 630, 638, 483, 455, 488, 635, 681, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {130, 195, 57, 107, 128, 146, 205, 234, 168, 109, -29, 25, 22, 11, 180, 289, 115, -8, -156, -122, -82, -123, 75, 182, 177, 21, -104, -96, -71, -80, 104, 
224, 223, 74, -45, 36, -32, 56, 111, 340, 221, 151, 19, 51, 204, 210, 244, 348, 299, 233, 129, 182, 130, 367, 257, 410, -52, -56, 29, 193, 282, 171, 71, 131};
constexpr int KnightPSTEg[] = {386, 245, 220, 222, 212, 189, 266, 383, 270, 220, 60, 63, 62, 34, 189, 322, 233, 72, -106, -77, -86, -136, 49, 230, 272, 92, -47, -52, -36, -79, 98, 249, 263, 125, -52, -41, -30, -55, 126, 240, 244, 81, -90, -81, -130, -145, 47, 201, 304, 263, 68, 71, 52, 0, 251, 245, 260, 320, 273, 225, 244, 164, 318, 185};

constexpr int BishopPSTMg[] = {263, 311, 244, 201, 218, 214, 250, 313, 299, 282, 299, 225, 254, 266, 337, 304, 267, 284, 258, 240, 247, 247, 287, 323, 244, 231, 232, 295, 276, 230, 224, 265, 252, 251, 297, 349, 319, 301, 253, 254, 284, 326, 313, 365, 369, 503, 393, 381, 299, 307, 262, 219, 328, 364, 311, 336, 205, 156, 174, 8, 120, 211, 233, 163};
constexpr int BishopPSTEg[] = {254, 295, 241, 285, 274, 292, 253, 199, 309, 270, 241, 283, 288, 243, 262, 247, 313, 300, 285, 285, 294, 276, 271, 276, 297, 300, 300, 264, 249, 278, 299, 281, 312, 315, 268, 266, 250, 275, 303, 311, 328, 288, 270, 238, 243, 253, 268, 320, 257, 272, 282, 282, 238, 245, 286, 236, 285, 320, 299, 356, 320, 279, 275, 274};

constexpr int RookPSTMg[] = {448, 448, 448, 461, 474, 442, 506, 460, 381, 416, 444, 441, 468, 480, 541, 433, 387, 412, 403, 437, 462, 476, 592, 513, 406, 410, 422, 457, 463, 468, 535, 503, 450, 487, 478, 509, 520, 569, 613, 576, 463, 539, 537, 529, 665, 682, 834, 702, 510, 505, 549, 626, 565, 724, 668, 717, 570, 545, 582, 590, 654, 685, 653, 659};
constexpr int RookPSTEg[] = {825, 833, 846, 815, 795, 805, 807, 788, 810, 816, 818, 805, 779, 772, 748, 772, 833, 831, 820, 813, 794, 784, 730, 744, 852, 859, 863, 829, 828, 830, 798, 785, 875, 864, 887, 864, 826, 815, 803, 796, 884, 885, 886, 868, 831, 820, 794, 786, 898, 933, 933, 888, 897, 864, 864, 829, 891, 908, 924, 907, 882, 877, 880, 878};

constexpr int QueenPSTMg[] = {1166, 1155, 1173, 1214, 1201, 1120, 1197, 1191, 1194, 1220, 1254, 1255, 1248, 1259, 1276, 1311, 1201, 1229, 1197, 1226, 1225, 1236, 1291, 1268, 1209, 1194, 1209, 1211, 1222, 1240, 1258, 1272, 1190, 1216, 1226, 1236, 1226, 1281, 1297, 1299, 1247, 1236, 1241, 1272, 1361, 1456, 1526, 1451, 1256, 1177, 1207, 1158, 1184, 1360, 1316, 1452, 
1137, 1169, 1274, 1371, 1365, 1410, 1426, 1252};
constexpr int QueenPSTEg[] = {1458, 1469, 1481, 1487, 1435, 1441, 1356, 1377, 1464, 1468, 1473, 1506, 1523, 1407, 1347, 1295, 1477, 1547, 1615, 1602, 1607, 1578, 1530, 1506, 1516, 1637, 1647, 1714, 1717, 1674, 1641, 1604, 1576, 1634, 1674, 1751, 1804, 1741, 1704, 1640, 1561, 1614, 1745, 1747, 1752, 1694, 1563, 1558, 1541, 1675, 1742, 1805, 1853, 1721, 1677, 1590, 
1617, 1649, 1687, 1661, 1668, 1610, 1512, 1600};

constexpr int KingPSTMg[] = {98, 176, 141, -107, 85, -76, 133, 136, 163, 78, 73, -35, -37, -28, 117, 83, -49, 40, -128, -162, -169, -169, -49, -141, -162, -148, -226, -312, -302, -214, -253, -391, -131, -159, -158, -311, -258, -203, -230, -319, -247, 64, -125, -128, -33, 142, 71, -56, -205, -64, -167, 24, -69, -14, 99, 41, -83, -104, -61, -206, -125, -25, 48, 66};constexpr int KingPSTEg[] = {-229, -153, -91, -39, -113, -43, -130, -251, -138, -21, 22, 59, 70, 50, -29, -112, -79, 23, 115, 157, 160, 130, 46, -27, -53, 77, 178, 239, 237, 180, 118, 37, -25, 118, 195, 257, 255, 227, 171, 66, 12, 106, 188, 218, 224, 202, 174, 52, -43, 82, 123, 106, 155, 185, 136, 18, -293, -130, -81, 22, -9, 0, -25, -293};

constexpr int PawnBonusMg[] = {21, -6, -21, 20, -6, 36, 25, -60};
constexpr int PawnBonusEg[] = {50, 73, 96, 116, 136, 148, 171, 153};

constexpr int DoubledPawnMg = -10;
constexpr int DoubledPawnEg = -62;

constexpr int IsolatedPawnBonusMg = -56;
constexpr int IsolatedPawnBonusEg = -45;

constexpr int PawnValueMg = 170;
constexpr int PawnValueEg = 226;

constexpr int KnightValueMg = 370;
constexpr int KnightValueEg = 398;

constexpr int BishopValueMg = 683;
constexpr int BishopValueEg = 715;

constexpr int RookValueMg = 807;
constexpr int RookValueEg = 1154;

constexpr int QueenValueMg = 1697;
constexpr int QueenValueEg = 2080;

constexpr int VirtualQueenMg = -20;
constexpr int VirtualQueenEg = -5;

constexpr int PawnShieldMg = 57;
constexpr int PawnShieldEg = -30;

constexpr int KnightMobilityMg = 102;
constexpr int KnightMobilityEg = 108;

constexpr int BishopMobilityMg = 27;
constexpr int BishopMobilityEg = 24;

constexpr int RookOnOpenFileMg = 128;
constexpr int RookOnOpenFileEg = 45;

constexpr uint64_t FILE_MASKS[8] = {
    0x0101010101010101ULL,
    0x0202020202020202ULL,
    0x0404040404040404ULL,
    0x0808080808080808ULL,
    0x1010101010101010ULL,
    0x2020202020202020ULL,
    0x4040404040404040ULL,
    0x8080808080808080ULL
};

constexpr uint64_t RankMasks[8] = {
    0x00000000000000FFULL, // Rank 1
    0x000000000000FF00ULL, // Rank 2
    0x0000000000FF0000ULL, // Rank 3
    0x00000000FF000000ULL, // Rank 4
    0x000000FF00000000ULL, // Rank 5
    0x0000FF0000000000ULL, // Rank 6
    0x00FF000000000000ULL, // Rank 7
    0xFF00000000000000ULL  // Rank 8
};

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

    const chess::Bitboard& WhitePawns,
    const chess::Bitboard& BlackPawns,

    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    const int RookOnOpenFileBonus = TaperedEval(RookOnOpenFileMg, RookOnOpenFileEg, GamePhase);
    const int TaperedRookValue = TaperedEval(RookValueMg, RookValueEg, GamePhase);
    const chess::Bitboard CombinedPawnBitboard = WhitePawns | BlackPawns;

    WhiteScore += WhiteRooks.count() * TaperedRookValue;
    BlackScore += BlackRooks.count() * TaperedRookValue;

    chess::Bitboard WhiteRookLocations = WhiteRooks;
    chess::Bitboard BlackRookLocations = BlackRooks;

    while (WhiteRookLocations != 0) {
        const uint8_t Index = WhiteRookLocations.pop();
        const uint8_t File  = Index & 7;

        WhiteScore += ((CombinedPawnBitboard & FILE_MASKS[File]) == 0) * RookOnOpenFileBonus;
        WhiteScore += TaperedEval(RookPSTMg[Index], RookPSTEg[Index], GamePhase);
    }

    while (BlackRookLocations != 0) {
        const uint8_t Index    = BlackRookLocations.pop();
        const uint8_t PSTIndex = MirrorSquare(Index);
        const uint8_t File     = Index & 7;

        BlackScore += ((CombinedPawnBitboard & FILE_MASKS[File]) == 0) * RookOnOpenFileBonus;
        BlackScore += TaperedEval(RookPSTMg[PSTIndex], RookPSTEg[PSTIndex], GamePhase);
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