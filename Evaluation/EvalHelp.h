#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -111, 102, -10, -148, -79, -76, 61, -142, -125, 58, 9, 79, 103, -18, 5, -139, -137, 54, 104, 194, 239, 78, 36, -160, -19, 120, 177, 169, 79, 31, 87, -57, 29, 208, 193, 180, 153, 127, 69, 63, 6, 14, 167, 420, 360, 154, -49, -81, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 80, 67, 72, 271, 258, 77, 78, 115, 85, 89, 22, 51, 28, 13, 128, 82, 92, 77, -26, -19, -59, -26, 84, 95, 94, 95, -19, -20, 47, 60, 106, 120, 261, 130, 3, 60, 50, 93, 225, 197, 659, 464, 529, 173, 282, 416, 818, 641, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {-362, -103, -99, -87, -66, 13, -112, -295, -94, -118, 13, 86, 74, 20, -55, -129, -54, 150, 204, 199, 176, 213, 74, -122, 127, 120, 233, 200, 149, 221, 119, 105, 328, 200, 403, 281, 249, 355, 174, 212, 236, 442, -90, 458, 436, -112, 441, 231, 98, -43, 452, -233, 158, 410, 158, 173, 10, -13, -524, -307, -194, -564, -187, -60};
constexpr int KnightPSTEg[] = {193, 127, 118, 144, 66, 57, 75, -16, 165, 233, 220, 252, 194, 257, 149, 226, 131, 245, 164, 333, 321, 166, 239, 160, 168, 286, 347, 384, 444, 350, 284, 116, 195, 368, 369, 402, 428, 437, 323, 129, 138, 86, 632, 339, 360, 589, 255, 211, 37, 352, 263, 569, 436, 277, 212, 141, -213, 211, 308, 444, 273, 283, 194, -318};        

constexpr int BishopPSTMg[] = {144, 185, 77, 60, 15, 70, 217, 54, 183, 329, 310, 214, 127, 241, 292, 318, 243, 217, 268, 225, 246, 208, 235, 201, 191, 182, 213, 271, 255, 264, 175, 114, 275, 229, 324, 374, 300, 210, 203, 211, 358, 275, -468, 161, 81, -520, 289, 302, 221, 76, 71, -599, -593, 103, 204, 91, 242, -393, -375, -720, -399, -679, -396, 148};    
constexpr int BishopPSTEg[] = {99, 170, 125, 186, 177, 42, 1, 213, 133, 181, 249, 203, 284, 246, 180, 117, 202, 336, 278, 318, 331, 314, 304, 154, 195, 348, 363, 360, 407, 319, 310, 324, 192, 331, 324, 366, 423, 364, 327, 280, 206, 403, 601, 354, 459, 588, 325, 230, 64, 389, 401, 547, 585, 345, 299, 142, 135, 404, 431, 414, 339, 465, 543, 275};

constexpr int RookPSTMg[] = {-24, -5, 91, 149, 137, 23, 30, -16, -84, 66, -10, 58, 7, -30, -20, -80, -130, -40, -1, 66, -9, -66, 38, 3, 56, 64, -60, 35, 38, -93, -99, 35, 198, 145, 202, 206, 260, 41, 104, 127, 358, 360, 302, 275, 247, 165, 241, 331, 448, 217, 354, 309, 270, 277, 68, 220, 294, 63, -533, -656, -337, -230, 288, 366};
constexpr int RookPSTEg[] = {300, 405, 244, 331, 322, 364, 346, 310, 293, 311, 367, 373, 341, 396, 305, 299, 471, 415, 349, 365, 384, 432, 326, 324, 473, 404, 516, 456, 467, 474, 464, 414, 407, 455, 460, 506, 442, 591, 500, 494, 443, 441, 528, 537, 475, 568, 532, 407, 420, 581, 570, 599, 604, 597, 597, 505, 523, 586, 759, 828, 688, 657, 429, 470};       

constexpr int QueenPSTMg[] = {40, -15, 15, 224, 30, -3, 40, 30, 99, 172, 224, 88, 58, 203, 141, 148, 97, 156, 75, 54, 36, 11, 191, 144, 75, 124, 52, 72, 48, 79, 81, 101, 251, 73, 149, 195, 154, 145, 123, 80, 326, 432, 206, 205, 294, 352, 396, 287, 288, 267, 226, 162, 101, 224, 135, 372, 355, 202, 568, 161, 260, 554, 486, 259};
constexpr int QueenPSTEg[] = {889, 635, 506, -143, 773, 589, 587, 573, 586, 507, 564, 824, 885, 528, 698, 722, 766, 766, 1020, 1012, 992, 1205, 680, 699, 869, 906, 1078, 1282, 1289, 985, 1101, 911, 825, 1208, 1107, 1233, 1208, 1135, 1127, 1314, 699, 945, 1097, 1114, 1032, 1031, 835, 739, 774, 844, 1177, 1211, 1319, 1050, 1075, 768, 688, 930, 968, 1155, 1156, 883, 869, 881};

constexpr int KingPSTMg[] = {96, 199, -9, -46, 28, -43, 240, 156, -2, 3, -94, -315, -357, -162, 51, 36, -364, -293, -429, -545, -470, -448, -190, -260, -542, -845, -705, -581, -590, -638, -508, -848, -89, -490, -720, -558, -568, -626, -493, -136, -39, -600, -239, 279, -72, -366, -861, -185, 272, -209, -380, -330, -86, 286, -410, 20, 34, -36, -53, -65, 75, 34, 115, 54};
constexpr int KingPSTEg[] = {-287, -276, -158, -193, -331, -137, -261, -327, -175, -71, -22, 60, 87, 8, -98, -174, -33, 40, 113, 170, 185, 125, 34, -61, 90, 240, 239, 307, 301, 250, 156, 136, 48, 250, 314, 279, 360, 296, 210, 1, 177, 439, 376, 329, 317, 388, 375, 42, -19, 342, 324, 355, 370, 288, 426, 36, -442, 114, 190, 299, 81, -93, -29, -421};        

constexpr int PawnBonusMg[] = {-111, -123, -123, -23, -61, 97, 83, 206};
constexpr int PawnBonusEg[] = {-41, 44, 62, 90, 116, 96, 160, -5};

constexpr int PawnValueMg = 332;
constexpr int PawnValueEg = 459;

constexpr int KnightValueMg = 612;
constexpr int KnightValueEg = 1520;

constexpr int BishopValueMg = 788;
constexpr int BishopValueEg = 1526;

constexpr int RookValueMg = 1086;
constexpr int RookValueEg = 2557;

constexpr int QueenValueMg = 3038;
constexpr int QueenValueEg = 4086;

static constexpr uint64_t MIDDLE_SQUARES =  0x0000001818000000ULL;
static constexpr uint64_t NOT_HFILE      = ~0x8080808080808080ULL;
static constexpr uint64_t NOT_AFILE      = ~0x0101010101010101ULL;
static constexpr uint64_t RANK2          =  0x000000000000FF00ULL;

inline void FindPassedPawns(
    const chess::Bitboard& WhitePawns, 
    const chess::Bitboard& BlackPawns,

    chess::Bitboard& WhitePassedPawns,
    chess::Bitboard& BlackPassedPawns
){  
    // PPE Algorithm, Simultaneously analyses pawns form both sides to determine if they are passed pawns Branchless and O(1).
    // Get Diagonals
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

    FindPassedPawns(WhitePawns, BlackPawns, WhitePassedPawns, BlackPassedPawns);

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
    chess::Bitboard WhiteKingLocations = WhiteKing;
    chess::Bitboard BlackKingLocations = BlackKing;

    while (WhiteKingLocations != 0) {
        uint8_t Index = WhiteKingLocations.pop();
        WhiteScore += TaperedEval(KingPSTMg[Index], KingPSTEg[Index], GamePhase);
    }

    while (BlackKingLocations != 0) {
        uint8_t Index = 63 - BlackKingLocations.pop();
        BlackScore += TaperedEval(KingPSTMg[Index], KingPSTEg[Index], GamePhase);
    }
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