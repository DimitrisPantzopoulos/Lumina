#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -16, 3, 13, -3, 54, 78, 107, 8, -6, 5, 47, 63, 104, 105, 132, 82, 0, 21, 65, 126, 129, 133, 76, 56, 40, 59, 98, 128, 194, 176, 123, 95, 98, 95, 222, 269, 288, 364, 248, 137, 393, 446, 375, 481, 447, 395, 140, 61, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 158, 141, 136, 125, 153, 118, 89, 106, 136, 127, 99, 98, 92, 89, 74, 77, 156, 139, 101, 73, 69, 79, 98, 91, 233, 191, 145, 93, 81, 99, 146, 152, 445, 459, 346, 253, 222, 222, 364, 361, 691, 642, 647, 492, 460, 491, 646, 693, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {149, 201, 66, 116, 135, 158, 214, 242, 179, 118, -24, 28, 27, 17, 188, 297, 120, -4, -157, -121, -81, -123, 82, 189, 182, 24, -103, -93, -68, -79, 105, 
230, 226, 78, -45, 34, -33, 59, 114, 344, 210, 145, 16, 51, 197, 205, 241, 347, 279, 240, 126, 191, 121, 354, 252, 415, -70, -69, 34, 184, 284, 150, 73, 97};
constexpr int KnightPSTEg[] = {392, 246, 222, 225, 216, 190, 270, 391, 276, 228, 60, 63, 63, 37, 192, 326, 236, 75, -107, -77, -87, -136, 46, 232, 275, 94, -48, -54, -37, -79, 99, 252, 264, 125, -53, -42, -31, -59, 124, 239, 248, 83, -90, -82, -129, -148, 48, 202, 312, 263, 69, 69, 55, 0, 255, 244, 263, 323, 275, 231, 243, 167, 320, 191};

constexpr int BishopPSTMg[] = {270, 320, 250, 207, 227, 222, 262, 325, 305, 289, 309, 233, 262, 277, 344, 311, 270, 291, 267, 248, 256, 257, 294, 328, 250, 238, 239, 304, 283, 236, 232, 274, 250, 260, 299, 354, 326, 307, 261, 262, 285, 328, 320, 366, 371, 500, 393, 379, 278, 305, 265, 223, 326, 359, 309, 332, 192, 154, 173, -1, 111, 193, 227, 147};
constexpr int BishopPSTEg[] = {256, 298, 245, 287, 276, 294, 253, 197, 311, 272, 242, 284, 289, 244, 263, 247, 316, 300, 287, 285, 295, 278, 272, 277, 298, 303, 301, 265, 250, 279, 301, 279, 312, 315, 270, 268, 251, 276, 304, 311, 329, 290, 271, 241, 245, 257, 271, 323, 266, 275, 285, 286, 242, 246, 290, 240, 291, 323, 301, 361, 325, 286, 279, 281};

constexpr int RookPSTMg[] = {470, 456, 447, 463, 477, 462, 507, 481, 399, 417, 442, 444, 470, 487, 535, 443, 401, 405, 401, 436, 463, 480, 600, 531, 404, 395, 417, 447, 451, 460, 534, 507, 445, 473, 465, 506, 510, 556, 596, 568, 456, 524, 524, 529, 652, 672, 799, 689, 509, 508, 550, 630, 565, 717, 673, 723, 556, 545, 581, 592, 641, 695, 656, 638};
constexpr int RookPSTEg[] = {828, 826, 842, 810, 787, 800, 795, 789, 801, 809, 814, 801, 773, 759, 739, 763, 824, 827, 812, 809, 784, 774, 722, 736, 849, 856, 856, 826, 826, 821, 791, 780, 872, 862, 886, 859, 822, 812, 804, 797, 882, 882, 879, 861, 826, 815, 799, 787, 895, 928, 927, 881, 892, 862, 862, 827, 891, 904, 920, 900, 880, 869, 876, 882};

constexpr int QueenPSTMg[] = {1187, 1178, 1195, 1236, 1220, 1149, 1224, 1211, 1213, 1242, 1276, 1275, 1269, 1279, 1304, 1329, 1218, 1250, 1220, 1247, 1246, 1257, 1310, 1290, 1227, 1212, 1230, 1229, 1242, 1260, 1281, 1293, 1200, 1233, 1244, 1254, 1245, 1298, 1312, 1318, 1256, 1252, 1253, 1292, 1363, 1469, 1518, 1462, 1247, 1190, 1220, 1179, 1197, 1352, 1327, 1465, 
1138, 1173, 1280, 1382, 1385, 1419, 1422, 1251};
constexpr int QueenPSTEg[] = {1474, 1478, 1493, 1491, 1450, 1445, 1363, 1393, 1479, 1476, 1480, 1515, 1533, 1425, 1344, 1312, 1495, 1553, 1627, 1614, 1621, 1602, 1542, 1508, 1526, 1648, 1656, 1732, 1730, 1688, 1649, 1612, 1582, 1642, 1686, 1764, 1811, 1752, 1713, 1653, 1569, 1622, 1754, 1756, 1771, 1706, 1581, 1566, 1556, 1684, 1756, 1816, 1867, 1743, 1688, 1601, 
1637, 1669, 1706, 1676, 1680, 1625, 1535, 1623};

constexpr int KingPSTMg[] = {101, 181, 141, -106, 83, -76, 132, 133, 173, 88, 78, -35, -39, -19, 118, 82, -46, 49, -128, -160, -165, -161, -50, -141, -156, -144, -222, -309, -303, -210, -256, -391, -123, -152, -158, -311, -263, -208, -230, -331, -253, 65, -121, -131, -33, 136, 61, -61, -211, -57, -158, 26, -70, -13, 102, 45, -86, -102, -56, -209, -123, -28, 49, 70};
constexpr int KingPSTEg[] = {-230, -154, -91, -39, -112, -42, -129, -251, -139, -22, 22, 59, 71, 49, -27, -112, -79, 22, 115, 158, 160, 129, 47, -28, -55, 76, 176, 239, 237, 180, 118, 36, -28, 116, 194, 255, 256, 227, 171, 67, 11, 104, 185, 217, 223, 202, 176, 51, -46, 78, 120, 104, 153, 184, 134, 17, -300, -136, -84, 18, -10, -1, -26, -294};

constexpr int PawnBonusMg[] = {18, -10, -24, 16, -9, 35, 22, -64};
constexpr int PawnBonusEg[] = {51, 75, 98, 119, 138, 150, 175, 156};

constexpr int DoubledPawnMg = -35;
constexpr int DoubledPawnEg = -64;

constexpr int IsolatedPawnBonusMg = -53;
constexpr int IsolatedPawnBonusEg = -44;

constexpr int PawnValueMg = 187;
constexpr int PawnValueEg = 228;

constexpr int KnightValueMg = 373;
constexpr int KnightValueEg = 401;

constexpr int BishopValueMg = 694;
constexpr int BishopValueEg = 718;

constexpr int RookValueMg = 819;
constexpr int RookValueEg = 1155;

constexpr int QueenValueMg = 1719;
constexpr int QueenValueEg = 2096;

constexpr int VirtualQueenMg = -20;
constexpr int VirtualQueenEg = -5;

constexpr int PawnShieldMg = 55;
constexpr int PawnShieldEg = -31;

constexpr int KnightMobilityMg = 103;
constexpr int KnightMobilityEg = 108;

constexpr int BishopMobilityMg = 26;
constexpr int BishopMobilityEg = 25;

constexpr int RookOnOpenFileMg = 149;
constexpr int RookOnOpenFileEg = 58;

constexpr int RookOnSemiOpenFileMg = 70;
constexpr int RookOnSemiOpenFileEg = 45;

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
    const int RookOnSemiOpenFile      = TaperedEval(RookOnSemiOpenFileMg, RookOnSemiOpenFileEg, GamePhase);
    const int RookOnOpenFile          = TaperedEval(RookOnOpenFileMg,     RookOnOpenFileEg,     GamePhase);
    const int TaperedRookValue        = TaperedEval(RookValueMg, RookValueEg, GamePhase);
    const chess::Bitboard CombinedPawnBitboard = WhitePawns | BlackPawns;

    WhiteScore += WhiteRooks.count() * TaperedRookValue;
    BlackScore += BlackRooks.count() * TaperedRookValue;

    chess::Bitboard WhiteRookLocations = WhiteRooks;
    chess::Bitboard BlackRookLocations = BlackRooks;

    while (WhiteRookLocations != 0) {
        const uint8_t Index = WhiteRookLocations.pop();
        const uint64_t File  = FILE_MASKS[Index & 7];

        WhiteScore += ((CombinedPawnBitboard & File) == 0) * RookOnOpenFile;
        WhiteScore += ((File & WhitePawns) == 0 && (File & BlackPawns) != 0) * RookOnSemiOpenFile;
        WhiteScore += TaperedEval(RookPSTMg[Index], RookPSTEg[Index], GamePhase);
    }

    while (BlackRookLocations != 0) {
        const uint8_t Index    = BlackRookLocations.pop();
        const uint8_t PSTIndex = MirrorSquare(Index);
        const uint64_t File     = FILE_MASKS[Index & 7];

        BlackScore += ((CombinedPawnBitboard & File) == 0) * RookOnOpenFile;
        BlackScore += ((File & BlackPawns) == 0 && (File & WhitePawns) != 0) * RookOnSemiOpenFile;
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