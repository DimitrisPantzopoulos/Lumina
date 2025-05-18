#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -90, -10, -59, -184, -207, 107, 124, 19, -63, -14, 27, 52, 122, 97, 138, 46, -56, 0, 120, 278, 231, 98, 75, 36, -6, 47, 68, 150, 218, 210, 154, 101, 93, 
151, 214, 285, 252, 384, 252, 190, 338, 452, 327, 407, 427, 385, 171, -19, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 191, 151, 201, 342, 462, 96, 79, 114, 147, 134, 114, 123, 95, 86, 76, 96, 168, 146, 62, -20, 9, 88, 91, 102, 252, 196, 174, 96, 83, 88, 130, 149, 432, 401, 311, 233, 218, 200, 326, 325, 701, 665, 655, 520, 463, 524, 661, 705, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {202, 196, 80, 141, 158, 209, 69, 273, 173, 117, -12, 9, -23, 23, 202, 295, 123, 32, -137, -148, -104, -123, 105, 161, 247, 56, -97, -100, -68, -90, 124, 300, 302, 131, 2, 15, 
-61, 131, 152, 446, 288, 249, 5, 108, 245, 213, 348, 393, 362, 273, 236, 240, 181, 401, 330, 497, 68, 18, 73, 146, 418, 89, 83, 191};
constexpr int KnightPSTEg[] = {337, 297, 216, 171, 177, 155, 436, 377, 237, 183, 44, 62, 82, 2, 168, 310, 236, 54, -161, -79, -107, -191, 29, 234, 266, 79, -62, -49, -49, -84, 73, 183, 249, 101, -69, -9, -16, -85, 106, 199, 233, 50, -88, -109, -131, -142, 17, 197, 291, 269, 49, 68, 51, 0, 231, 239, 277, 314, 305, 263, 198, 202, 288, 204};

constexpr int BishopPSTMg[] = {361, 462, 370, 356, 372, 305, 471, 436, 550, 504, 557, 440, 454, 524, 598, 493, 484, 558, 481, 547, 491, 513, 516, 534, 484, 505, 575, 576, 569, 540, 496, 445, 458, 557, 627, 
680, 635, 612, 530, 466, 501, 618, 514, 682, 602, 621, 606, 598, 523, 560, 513, 448, 565, 611, 537, 520, 460, 411, 334, 98, 261, 339, 395, 449};
constexpr int BishopPSTEg[] = {355, 403, 319, 395, 372, 431, 324, 243, 361, 361, 380, 429, 458, 365, 342, 327, 409, 441, 456, 455, 486, 423, 413, 402, 386, 482, 473, 491, 477, 457, 454, 406, 426, 460, 442, 
483, 478, 470, 446, 423, 458, 441, 464, 426, 460, 499, 429, 418, 360, 445, 457, 473, 415, 414, 475, 333, 390, 454, 439, 493, 466, 428, 414, 401};

constexpr int RookPSTMg[] = {457, 476, 515, 516, 529, 456, 522, 454, 371, 425, 497, 479, 474, 475, 600, 461, 397, 460, 418, 450, 470, 465, 602, 543, 457, 441, 484, 522, 476, 423, 563, 516, 516, 557, 592, 607, 618, 628, 697, 680, 646, 697, 649, 671, 781, 760, 898, 837, 692, 645, 734, 795, 708, 854, 756, 907, 732, 699, 774, 719, 794, 727, 798, 762};
constexpr int RookPSTEg[] = {807, 828, 840, 836, 802, 783, 824, 800, 794, 797, 829, 827, 795, 789, 724, 762, 847, 833, 851, 856, 830, 779, 750, 740, 858, 881, 881, 860, 860, 867, 793, 793, 890, 892, 905, 908, 843, 822, 794, 775, 855, 876, 898, 880, 842, 821, 791, 767, 869, 927, 932, 917, 915, 866, 856, 793, 880, 897, 916, 939, 892, 892, 867, 872};

constexpr int QueenPSTMg[] = {1245, 1234, 1249, 1300, 1290, 1189, 1272, 1282, 1237, 1284, 1349, 1312, 1271, 1362, 1419, 1489, 1309, 1335, 1244, 1252, 1257, 1286, 1398, 1341, 1255, 1267, 1245, 1180, 1276, 1280, 1338, 1361, 1278, 1289, 1321, 1293, 1294, 1352, 1342, 1316, 1370, 1378, 1356, 1407, 1448, 1561, 1606, 1543, 1339, 1273, 1312, 1280, 1306, 1443, 1408, 1574, 1096, 1241, 1348, 1432, 1423, 1504, 1469, 1320};
constexpr int QueenPSTEg[] = {1422, 1410, 1431, 1408, 1431, 1409, 1354, 1380, 1466, 1411, 1429, 1501, 1601, 1386, 1202, 1201, 1454, 1492, 1635, 1660, 1659, 1615, 1480, 1474, 1589, 1629, 1668, 1943, 1723, 1692, 1631, 1573, 1586, 1671, 1657, 1797, 1819, 1750, 1743, 1751, 1527, 1577, 1701, 1690, 1746, 1695, 1582, 1538, 1531, 1635, 1717, 1763, 1825, 1729, 1643, 1534, 1676, 1659, 1702, 1670, 1699, 1614, 1536, 1577};

constexpr int KingPSTMg[] = {148, 264, 173, -213, 48, -126, 191, 192, 168, -17, 22, -108, -139, -51, 94, 120, -74, 8, -196, -211, -253, -239, -49, -186, -229, -239, -298, -343, -369, -303, -286, -418, -165, -196, -199, -345, -320, -239, -227, -370, -262, -123, -149, -157, -52, 117, -1, -81, -156, -125, -188, -40, -119, 45, 48, 93, -94, -59, -59, -136, -139, 32, -29, 18};
constexpr int KingPSTEg[] = {-254, -218, -121, -30, -92, -31, -171, -303, -158, -16, 43, 83, 107, 54, -45, -148, -99, 31, 147, 186, 196, 153, 48, -24, -32, 110, 225, 280, 287, 233, 142, 38, -12, 150, 241, 311, 304, 257, 174, 81, 30, 180, 236, 259, 278, 234, 211, 62, -25, 134, 160, 172, 199, 210, 189, -17, -314, -127, -53, 28, -5, 0, 16, -327};

constexpr int PawnBonusMg[] = {1, -25, -49, 40, -40, 96, 74, 48};
constexpr int PawnBonusEg[] = {30, 63, 99, 99, 152, 120, 162, 103};

constexpr int DoubledPawnMg = -42;
constexpr int DoubledPawnEg = -48;

constexpr int IsolatedPawnBonusMg = -89;
constexpr int IsolatedPawnBonusEg = -52;

constexpr int PawnValueMg = 263;
constexpr int PawnValueEg = 234;

constexpr int KnightValueMg = 356;
constexpr int KnightValueEg = 410;

constexpr int BishopValueMg = 797;
constexpr int BishopValueEg = 736;

constexpr int RookValueMg = 1022;
constexpr int RookValueEg = 1208;

constexpr int QueenValueMg = 1972;
constexpr int QueenValueEg = 2194;

constexpr int VirtualQueenMg = -13;
constexpr int VirtualQueenEg = -9;

constexpr int PawnShieldMg = 38;
constexpr int PawnShieldEg = -13;

constexpr int KnightMobilityMg = 122;
constexpr int KnightMobilityEg = 108;

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
        uint8_t Index = MirrorSquare(BlackBishopLocations.pop());
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