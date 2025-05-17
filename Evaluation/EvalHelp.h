#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -72, -15, -80, -23, -62, 105, 75, 32, -59, -35, 6, 63, 132, 106, 51, 20, -86, -24, 119, 218, 184, 97, 16, -14, -62, 28, 9, 154, 158, 123, 88, 63, -33, 142, 71, 160, 128, 218, 95, 91, 119, 256, 101, 77, 295, 348, 28, -150, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 144, 114, 189, 229, 332, 78, 68, 95, 111, 131, 137, 126, 86, 81, 95, 95, 130, 123, 53, 16, 56, 82, 92, 107, 196, 146, 156, 93, 92, 92, 108, 110, 318, 184, 163, 132, 91, 106, 192, 173, 534, 557, 492, 423, 275, 476, 511, 547, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {47, 99, 5, 73, 55, 130, 32, 25, 88, 68, -19, 59, 20, 18, 106, 139, 39, 54, -37, -20, 27, -17, 83, 61, 158, 33, 10, -38, -7, 25, 39, 177, 191, 113, 68, 33, -24, 154, 135, 362, 109, 199, -52, 162, 277, 104, 287, 155, 124, 77, 162, 196, 93, 253, 209, 224, -172, -98, -333, -312, 177, -302, -285, -145};
constexpr int KnightPSTEg[] = {97, 133, 205, 37, 95, 113, 227, 297, 311, 226, 52, -14, 28, -10, 93, 170, 171, 36, -131, -31, -103, -155, 12, 132, 230, 64, -59, 4, -2, -79, 59, 79, 179, 64, -19, 51, -3, -33, 48, 100, 184, 24, -21, -95, -115, 1, 25, 180, 183, 209, 75, 61, 112, -4, 158, 243, 203, 314, 366, 300, 127, 236, 153, 189};

constexpr int BishopPSTMg[] = {212, 268, 178, 141, 146, 156, 360, 267, 397, 288, 311, 214, 237, 309, 370, 292, 282, 331, 222, 235, 205, 262, 275, 280, 331, 229, 233, 280, 250, 202, 195, 280, 225, 278, 280, 326, 263, 244, 258, 257, 297, 380, 308, 269, 226, 283, 348, 361, 215, 179, 142, 72, 268, 154, 137, 297, 200, 251, 160, -263, 25, 78, 183, 248};
constexpr int BishopPSTEg[] = {218, 194, 161, 210, 169, 210, 87, 117, 169, 172, 206, 197, 205, 129, 167, 137, 169, 231, 226, 228, 230, 188, 192, 279, 153, 257, 219, 202, 196, 193, 229, 247, 236, 210, 165, 204, 189, 215, 176, 241, 311, 260, 151, 180, 199, 201, 174, 165, 223, 266, 261, 315, 213, 197, 310, 91, 230, 315, 302, 316, 290, 286, 200, 292};

constexpr int RookPSTMg[] = {370, 384, 417, 414, 425, 385, 392, 352, 294, 333, 374, 393, 360, 353, 503, 348, 297, 360, 355, 301, 356, 344, 436, 429, 320, 271, 422, 382, 371, 268, 398, 327, 390, 371, 398, 452, 443, 474, 504, 541, 497, 523, 459, 454, 525, 571, 571, 622, 479, 386, 490, 519, 462, 456, 427, 647, 577, 374, 632, 330, 539, 235, 858, 337};
constexpr int RookPSTEg[] = {535, 526, 519, 506, 483, 502, 547, 539, 514, 513, 549, 533, 505, 537, 440, 441, 570, 539, 559, 567, 535, 477, 482, 466, 584, 590, 571, 583, 547, 581, 495, 532, 609, 618, 611, 615, 554, 527, 501, 482, 557, 581, 605, 590, 578, 545, 543, 533, 577, 655, 643, 630, 642, 657, 608, 523, 598, 613, 577, 707, 607, 715, 562, 679};

constexpr int QueenPSTMg[] = {843, 818, 811, 826, 822, 809, 836, 828, 736, 866, 896, 890, 840, 917, 1047, 1154, 911, 891, 810, 828, 840, 800, 907, 861, 793, 833, 800, 692, 824, 853, 853, 893, 851, 801, 811, 774, 789, 798, 840, 784, 901, 927, 881, 947, 909, 973, 1000, 1003, 786, 756, 832, 811, 796, 833, 816, 1037, 554, 927, 950, 951, 760, 1048, 978, 887};
constexpr int QueenPSTEg[] = {1025, 977, 984, 976, 1143, 979, 1051, 1082, 1234, 1083, 1013, 1062, 1183, 1081, 640, 842, 1069, 1063, 1286, 1265, 1275, 1362, 1115, 1030, 1239, 1189, 1256, 1787, 1303, 1250, 1285, 1086, 1273, 1373, 1335, 1463, 1459, 1401, 1419, 1528, 1145, 1214, 1281, 1216, 1445, 1433, 1279, 1134, 1246, 1291, 1295, 1335, 1423, 1434, 1538, 1139, 1357, 1227, 1280, 1296, 1513, 1262, 1331, 1187};

constexpr int KingPSTMg[] = {86, 170, 58, -307, -33, -177, 91, 89, -106, -19, -63, -166, -175, -65, 30, -10, -44, -48, -142, -166, -227, -206, -74, -264, -167, -334, -148, -187, -160, -273, -173, -380, -236, -42, -42, 15, -218, -34, -114, -228, -28, -600, 249, 139, 381, 160, -98, -16, 300, 173, -20, 197, -117, 550, 6, 316, 123, 400, 204, 382, -161, 434, -249, 65};
constexpr int KingPSTEg[] = {-213, -182, -114, 1, -88, -1, -156, -257, -43, 1, 53, 96, 104, 43, -23, -104, -116, 37, 139, 147, 161, 121, 51, 31, 12, 123, 196, 223, 226, 197, 121, 41, 16, 140, 200, 246, 224, 187, 111, 58, 34, 286, 201, 202, 254, 188, 199, 65, 8, 148, 142, 276, 224, 171, 224, -105, -276, -84, 69, 50, 92, 10, 47, -331};       

constexpr int PawnBonusMg[] = {-7, -15, 8, 59, 15, 117, 128, 164};
constexpr int PawnBonusEg[] = {8, 43, 68, 68, 110, 70, 130, 5};

constexpr int DoubledPawnMg = -92;
constexpr int DoubledPawnEg = -25;

constexpr int IsolatedPawnBonusMg = -88;
constexpr int IsolatedPawnBonusEg = -40;

constexpr int PawnValueMg = 286;
constexpr int PawnValueEg = 177;

constexpr int KnightValueMg = 591;
constexpr int KnightValueEg = 464;

constexpr int BishopValueMg = 775;
constexpr int BishopValueEg = 629;

constexpr int RookValueMg = 1047;
constexpr int RookValueEg = 1098;

constexpr int QueenValueMg = 1815;
constexpr int QueenValueEg = 2055;

constexpr int VirtualQueenMg = -7;
constexpr int VirtualQueenEg = -7;

constexpr int PawnShieldMg = 18;
constexpr int PawnShieldEg = -12;

constexpr int KnightMobilityMg = 68;
constexpr int KnightMobilityEg = 74;

constexpr int BishopMobilityMg = 29;
constexpr int BishopMobilityEg = 19;

constexpr int RookMobilityMg = 29;
constexpr int RookMobilityEg = 10;

static constexpr uint64_t MIDDLE_SQUARES =  0x0000001818000000ULL;
static constexpr uint64_t NOT_HFILE      = ~0x8080808080808080ULL;
static constexpr uint64_t NOT_AFILE      = ~0x0101010101010101ULL;
static constexpr uint64_t RANK2          =  0x000000000000FF00ULL;

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

    chess::Bitboard WhiteIsolatedPawns;
    chess::Bitboard BlackIsolatedPawns;

    chess::Bitboard WhiteDoubledPawns;
    chess::Bitboard BlackDoubledPawns;

    FindPassedPawns(WhitePawns, BlackPawns, WhitePassedPawns, BlackPassedPawns, WhiteScore, BlackScore, GamePhase);

    // Add the Isolated Pawns to the scores
    int IsolatedPawnBonus = TaperedEval(IsolatedPawnBonusMg, IsolatedPawnBonusEg, GamePhase);

    WhiteScore += WhiteIsolatedPawns.count() * IsolatedPawnBonus;
    BlackScore += BlackIsolatedPawns.count() * IsolatedPawnBonus;

    while(WhitePawnLocations != 0){
        uint8_t  Index    = WhitePawnLocations.pop();
        WhiteScore += TaperedEval(PawnPSTMg[Index], PawnPSTEg[Index], GamePhase);
    }

    while(BlackPawnLocations != 0){
        uint8_t Index = MirrorSquare(BlackPawnLocations.pop());
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

    int KnightMobilityBonus = TaperedEval(KnightMobilityMg, KnightMobilityEg, GamePhase);

    while(WhiteKnightLocations != 0){
        uint8_t Index = WhiteKnightLocations.pop();
        WhiteScore += chess::attacks::knight(Index).count() * KnightMobilityBonus;
        WhiteScore += TaperedEval(KnightPSTMg[Index], KnightPSTEg[Index], GamePhase);
    }

    while(BlackKnightLocations != 0){
        uint8_t Index = MirrorSquare(BlackKnightLocations.pop());
        BlackScore += chess::attacks::knight(Index).count() * KnightMobilityBonus;
        BlackScore += TaperedEval(KnightPSTMg[Index], KnightPSTEg[Index], GamePhase);
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
    int TaperedBishopValue = TaperedEval(BishopValueMg, BishopValueEg, GamePhase);

    WhiteScore += WhiteBishops.count() * TaperedBishopValue;
    BlackScore += BlackBishops.count() * TaperedBishopValue;

    chess::Bitboard WhiteBishopLocations = WhiteBishops;
    chess::Bitboard BlackBishopLocations = BlackBishops;


    int BishopMobilityBonus = TaperedEval(BishopMobilityMg, BishopMobilityEg, GamePhase);

    while(WhiteBishopLocations != 0){
        uint8_t Index = WhiteBishopLocations.pop();
        WhiteScore += chess::attacks::bishop(Index, OCC).count() * BishopMobilityBonus;
        WhiteScore += TaperedEval(BishopPSTMg[Index], BishopPSTEg[Index], GamePhase);
    }

    while(BlackBishopLocations != 0){
        uint8_t RawIndex = BlackBishopLocations.pop();
        uint8_t PSTIndex = MirrorSquare(RawIndex);

        BlackScore += chess::attacks::bishop(RawIndex, OCC).count() * BishopMobilityBonus;
        BlackScore += TaperedEval(BishopPSTMg[PSTIndex], BishopPSTEg[PSTIndex], GamePhase);
    }
}

inline void EvaluateRooks(
    const chess::Bitboard& WhiteRooks,
    const chess::Bitboard& BlackRooks,
    const chess::Bitboard& OCC,
    const int GamePhase,
    int& WhiteScore,
    int& BlackScore
){
    int TaperedRookValue = TaperedEval(RookValueMg, RookValueEg, GamePhase);

    WhiteScore += WhiteRooks.count() * TaperedRookValue;
    BlackScore += BlackRooks.count() * TaperedRookValue;

    chess::Bitboard WhiteRookLocations = WhiteRooks;
    chess::Bitboard BlackRookLocations = BlackRooks;

    int RookMobilityBonus = TaperedEval(RookMobilityMg, RookMobilityEg, GamePhase);

    while (WhiteRookLocations != 0) {
        uint8_t Index = WhiteRookLocations.pop();
        chess::Bitboard RookAttacks = chess::attacks::rook(Index, OCC);

        WhiteScore += (RookAttacks & FILE_MASKS[Index & 7]).count() * RookMobilityBonus;
        WhiteScore += TaperedEval(RookPSTMg[Index], RookPSTEg[Index], GamePhase);
    }

    while (BlackRookLocations != 0) {
        uint8_t RawIndex = BlackRookLocations.pop();
        uint8_t PSTIndex = MirrorSquare(RawIndex);
        chess::Bitboard RookAttacks = chess::attacks::rook(RawIndex, OCC);

        BlackScore += (RookAttacks & FILE_MASKS[RawIndex & 7]).count() * RookMobilityBonus;
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

#endif // EVALHELP_H