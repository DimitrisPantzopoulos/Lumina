#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -195, -30, -126, -165, -219, 80, 69, -62, -139, -22, 3, 5, 99, 58, 67, -55, -133, -16, 184, 275, 237, 58, 2, -85, -60, 63, 98, 184, 213, 239, 144, 84, 68, 148, 196, 193, 232, 256, 136, 177, 436, 192, 313, 374, 609, 166, 24, -80, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 139, 61, 178, 246, 481, 7, -6, 78, 79, 61, 81, 135, 73, 44, 21, 63, 104, 60, -50, -61, -46, 50, 24, 71, 171, 100, 102, 27, 18, 2, 44, 69, 276, 155, 70, 76, 17, 67, 189, 170, 588, 679, 393, 319, 89, 593, 462, 618, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {-454, -65, -111, -4, -35, 68, -169, -203, -140, -40, 71, 122, 81, 120, -3, -8, -59, 164, 213, 184, 271, 233, 233, -21, 139, 141, 298, 208, 268, 264, 196, 146, 159, 256, 384, 370, 286, 479, 263, 416, 172, 428, -95, 478, 516, -138, 483, 338, 119, 65, 567, -335, 383, 307, 203, 268, -216, -225, -483, -597, 168, -577, -26, -39};
constexpr int KnightPSTEg[] = {105, 100, 206, 84, 115, 35, 245, 183, 312, 238, 280, 236, 232, 173, 142, 121, 173, 242, 231, 383, 302, 178, 187, 168, 242, 314, 346, 428, 388, 358, 267, 127, 285, 302, 428, 450, 411, 412, 334, 111, 235, 162, 572, 333, 424, 804, 306, 166, 135, 332, 236, 595, 403, 369, 205, 120, -75, 302, 492, 465, 290, 121, 178, -309};      

constexpr int BishopPSTMg[] = {162, 243, 102, 107, 136, 51, 289, 193, 376, 339, 373, 199, 223, 337, 415, 340, 268, 364, 254, 311, 248, 323, 321, 276, 273, 262, 313, 334, 330, 328, 263, 231, 307, 300, 352, 438, 414, 335, 271, 262, 311, 370, -398, 281, 141, -600, 271, 380, 192, 299, 168, -716, -454, 20, -21, 236, 124, -632, -480, -588, -432, -554, -111, 387};
constexpr int BishopPSTEg[] = {180, 130, 124, 181, 113, 234, 34, 96, 120, 149, 250, 245, 264, 169, 142, 26, 180, 328, 299, 313, 362, 286, 225, 248, 182, 349, 346, 372, 351, 282, 269, 256, 194, 333, 329, 377, 356, 341, 274, 271, 331, 392, 532, 381, 426, 686, 338, 186, 173, 234, 411, 604, 553, 358, 459, 20, 116, 525, 447, 423, 327, 440, 431, 323};

constexpr int RookPSTMg[] = {-10, 34, 118, 95, 121, 5, 74, 0, -96, -42, 60, 59, 36, -20, 175, -47, -75, 30, 4, -23, 51, 24, 56, 73, 69, -106, 114, 33, 53, -106, 110, 63, 150, 84, 171, 283, 226, 129, 256, 246, 332, 297, 242, 267, 270, 324, 374, 402, 303, 174, 356, 364, 286, 321, 154, 471, 389, 157, 385, -361, -152, -1617, 126, 310};
constexpr int RookPSTEg[] = {281, 330, 294, 310, 270, 237, 337, 273, 278, 306, 336, 326, 297, 324, 201, 260, 408, 358, 408, 370, 330, 285, 296, 243, 432, 489, 428, 462, 396, 456, 308, 375, 443, 497, 504, 460, 405, 440, 344, 363, 430, 467, 523, 475, 472, 470, 397, 336, 448, 539, 551, 556, 557, 528, 557, 415, 482, 465, 426, 718, 602, 999, 532, 435};       

constexpr int QueenPSTMg[] = {326, 275, 261, 327, 297, 258, 207, 159, 205, 350, 410, 367, 295, 408, 485, 753, 396, 403, 270, 264, 286, 293, 446, 412, 285, 263, 305, 204, 351, 310, 377, 416, 375, 352, 425, 417, 410, 367, 327, 357, 457, 572, 501, 497, 498, 608, 577, 587, 486, 390, 408, 320, 413, 454, 555, 736, 364, 473, 790, 545, 431, 905, 716, 615};      
constexpr int QueenPSTEg[] = {602, 487, 541, 355, 658, 401, 804, 664, 801, 690, 572, 673, 853, 589, 319, 92, 826, 686, 1056, 952, 990, 1037, 701, 525, 931, 1063, 959, 1504, 1046, 984, 898, 679, 973, 1002, 996, 1166, 1184, 1133, 1243, 1143, 722, 862, 889, 984, 1074, 1214, 1015, 736, 786, 888, 1058, 1247, 1273, 1231, 1099, 658, 869, 940, 922, 1050, 1188, 791, 923, 848};

constexpr int KingPSTMg[] = {227, 336, 183, -299, 39, -157, 300, 277, -87, 62, -39, -186, -233, 16, 164, 150, -86, -165, -303, -310, -418, -304, -69, -205, -663, -613, -475, -520, -418, -530, -475, -586, 184, -213, -637, -399, -496, -362, -506, -353, -146, -784, -95, 18, 272, -91, -452, 83, 141, -513, -39, -91, -258, 1, -118, 155, -8, 268, -64, 227, -59, 195, -176, 137};
constexpr int KingPSTEg[] = {-284, -347, -254, -140, -212, -115, -345, -464, -151, -99, -4, 40, 84, -48, -141, -297, -241, 13, 138, 188, 205, 119, -10, -103, 37, 149, 264, 350, 317, 251, 161, 41, -86, 229, 337, 387, 322, 277, 194, 28, 114, 428, 432, 337, 356, 330, 338, -5, 26, 417, 268, 442, 319, 301, 331, -173, -449, -69, 100, 269, 175, -62, 54, -507}; 

constexpr int PawnBonusMg[] = {-42, -70, -59, 36, -10, 122, 124, 165};
constexpr int PawnBonusEg[] = {7, 96, 116, 105, 161, 123, 209, 60};

constexpr int DoubledPawnMg = -87;
constexpr int DoubledPawnEg = -71;

constexpr int IsolatedPawnBonusMg = -100;
constexpr int IsolatedPawnBonusEg = -60;

constexpr int PawnValueMg = 326;
constexpr int PawnValueEg = 398;

constexpr int KnightValueMg = 673;
constexpr int KnightValueEg = 1415;

constexpr int BishopValueMg = 833;
constexpr int BishopValueEg = 1449;

constexpr int RookValueMg = 1224;
constexpr int RookValueEg = 2468;

constexpr int QueenValueMg = 2973;
constexpr int QueenValueEg = 3983;

constexpr int VirtualQueenMg = -7;
constexpr int VirtualQueenEg = -13;

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

    while(WhiteKnightLocations != 0){
        uint8_t Index = WhiteKnightLocations.pop();
        WhiteScore += TaperedEval(KnightPSTMg[Index], KnightPSTEg[Index], GamePhase);
    }

    while(BlackKnightLocations != 0){
        uint8_t Index = MirrorSquare(BlackKnightLocations.pop());
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