#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PawnPSTMg[] = {0, 0, 0, 0, 0, 0, 0, 0, -87, 16, -59, -67, -100, 62, 98, -13, -66, -11, 19, 62, 117, 66, 78, 10, -53, -11, 138, 191, 175, 81, 30, 0, -15, 40, 53, 122, 150, 138, 105, 68, 44, 109, 195, 207, 210, 256, 172, 120, 278, 308, 253, 315, 314, 208, 17, -16, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int PawnPSTEg[] = {0, 0, 0, 0, 0, 0, 0, 0, 88, 41, 108, 164, 240, 30, -1, 29, 57, 54, 43, 30, 11, 21, 15, 22, 72, 64, -32, -53, -38, 17, 26, 28, 144, 103, 81, 18, 22, 24, 58, 64, 317, 290, 200, 142, 119, 126, 228, 220, 513, 495, 481, 359, 310, 400, 498, 536, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr int KnightPSTMg[] = {47, 45, 21, 65, 71, 116, -32, 110, 72, 68, -3, 55, 26, 50, 132, 155, 31, 34, -24, -10, 38, 4, 96, 57, 129, 43, 27, -4, 39, 24, 114, 176, 189, 117, 62, 111, 14, 137, 126, 303, 
156, 190, 6, 141, 203, 106, 259, 247, 173, 134, 252, 27, 180, 267, 166, 299, -118, -85, -147, -146, 222, -212, -74, -41};
constexpr int KnightPSTEg[] = {200, 214, 144, 110, 128, 95, 335, 242, 247, 168, 21, 7, 22, -24, 113, 248, 156, 34, -149, -76, -109, -179, 7, 176, 207, 63, -70, -38, -43, -77, 50, 138, 182, 70, -37, -19, 0, 
-36, 96, 158, 170, 21, -36, -66, -65, -42, 28, 148, 208, 208, 24, 120, 46, 24, 170, 173, 120, 219, 254, 243, 181, 171, 205, 75};

constexpr int BishopPSTMg[] = {148, 143, 87, 37, 66, 37, 160, 208, 209, 168, 140, 76, 87, 126, 245, 167, 140, 159, 100, 81, 65, 132, 137, 188, 183, 54, 101, 112, 94, 65, 60, 160, 112, 148, 108, 180, 133, 88, 124, 132, 143, 167, -204, 136, 74, -305, 172, 224, 127, 66, 56, -511, -84, 7, 45, 125, 30, -208, -123, -160, -60, -208, 24, 67};
constexpr int BishopPSTEg[] = {100, 145, 77, 136, 118, 162, 64, 15, 122, 98, 114, 134, 146, 103, 86, 91, 141, 168, 161, 162, 180, 125, 131, 132, 103, 197, 157, 174, 154, 154, 163, 132, 155, 151, 156, 159, 153, 177, 152, 155, 180, 166, 277, 149, 167, 361, 150, 146, 114, 160, 179, 352, 209, 180, 192, 86, 145, 249, 208, 213, 192, 209, 158, 152};

constexpr int RookPSTMg[] = {70, 81, 119, 119, 138, 73, 123, 66, 9, 66, 107, 105, 110, 96, 179, 60, 21, 68, 80, 86, 115, 107, 188, 145, 61, 46, 116, 124, 114, 57, 142, 106, 117, 140, 155, 198, 206, 203, 246, 256, 212, 254, 219, 251, 310, 329, 431, 388, 242, 208, 313, 351, 309, 382, 290, 468, 293, 232, 313, 178, 287, 80, 384, 381};
constexpr int RookPSTEg[] = {379, 409, 416, 415, 380, 363, 393, 369, 382, 400, 407, 407, 372, 372, 325, 354, 425, 419, 425, 428, 399, 368, 337, 324, 441, 461, 456, 456, 439, 439, 388, 387, 471, 471, 495, 478, 433, 409, 385, 372, 446, 458, 483, 464, 438, 414, 384, 360, 453, 505, 502, 498, 492, 454, 451, 379, 463, 484, 490, 539, 487, 521, 441, 437};

constexpr int QueenPSTMg[] = {414, 385, 403, 433, 437, 369, 405, 437, 393, 460, 486, 484, 452, 507, 565, 610, 447, 478, 438, 443, 454, 443, 524, 488, 418, 409, 440, 390, 467, 464, 483, 505, 440, 467, 466, 499, 501, 480, 508, 501, 505, 502, 509, 530, 549, 681, 695, 660, 502, 434, 462, 448, 456, 558, 588, 681, 392, 438, 556, 602, 589, 734, 724, 547};
constexpr int QueenPSTEg[] = {745, 743, 734, 709, 734, 703, 710, 667, 802, 758, 726, 773, 842, 705, 518, 486, 791, 784, 936, 912, 920, 970, 790, 750, 878, 955, 945, 1158, 989, 964, 921, 854, 871, 913, 954, 
1022, 1046, 1054, 1013, 988, 803, 877, 944, 995, 1054, 995, 859, 816, 786, 892, 1016, 1059, 1137, 1028, 905, 816, 882, 939, 968, 964, 982, 849, 781, 851};

constexpr int KingPSTMg[] = {151, 234, 159, -158, 57, -79, 179, 187, 151, 95, 31, -67, -81, 7, 144, 125, -68, -3, -138, -175, -201, -154, -32, -121, -242, -276, -235, -319, -313, -256, -266, -371, -146, -185, -240, -388, -320, -242, -227, -314, -247, -153, -192, -178, -48, 122, -8, -57, -143, -233, -189, 36, -123, 68, 47, 78, -57, 77, 2, -128, -125, 74, -3, 68};
constexpr int KingPSTEg[] = {-254, -206, -132, -55, -116, -58, -182, -291, -157, -55, 10, 44, 58, 7, -72, -156, -107, 8, 101, 133, 142, 100, 14, -53, -41, 88, 163, 222, 220, 171, 104, 16, -32, 116, 197, 257, 239, 202, 130, 43, 9, 150, 202, 205, 213, 185, 166, 20, -32, 116, 124, 110, 155, 156, 140, -47, -305, -160, -90, 10, -24, -42, -8, -358};

constexpr int PawnBonusMg[] = {-13, -36, -50, 10, -43, 50, 23, 13};
constexpr int PawnBonusEg[] = {44, 74, 102, 107, 150, 126, 168, 100};

constexpr int DoubledPawnMg = -23;
constexpr int DoubledPawnEg = -49;

constexpr int IsolatedPawnBonusMg = -58;
constexpr int IsolatedPawnBonusEg = -36;

constexpr int PawnValueMg = 209;
constexpr int PawnValueEg = 259;

constexpr int KnightValueMg = 406;
constexpr int KnightValueEg = 567;

constexpr int BishopValueMg = 637;
constexpr int BishopValueEg = 904;

constexpr int RookValueMg = 1072;
constexpr int RookValueEg = 1557;

constexpr int QueenValueMg = 2132;
constexpr int QueenValueEg = 2796;

constexpr int VirtualQueenMg = -9;
constexpr int VirtualQueenEg = -9;

constexpr int PawnShieldMg = 31;
constexpr int PawnShieldEg = -17;

constexpr int KnightMobilityMg = 61;
constexpr int KnightMobilityEg = 85;

constexpr int BishopMobilityMg = 37;
constexpr int BishopMobilityEg = 10;

constexpr int KnightKingRingAttackMg = 17;
constexpr int KnightKingRingAttackEg = -21;

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
    for(int i=0;i<8;i++){
        uint64_t RankBitboard = RANK2 << (8 * i);

        WhiteScore += (RankBitboard & WhitePassedPawns).count() * TaperedEval(PawnBonusMg[i],   PawnBonusEg[i],   GamePhase);
        BlackScore += (RankBitboard & BlackPassedPawns).count() * TaperedEval(PawnBonusMg[7-i], PawnBonusEg[7-i], GamePhase);
    }
}

inline void EvaluateKnights(
    const chess::Bitboard& WhiteKnights,
    const chess::Bitboard& BlackKnights,

    const chess::Bitboard& WhiteKingRing,
    const chess::Bitboard& BlackKingRing,

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
    int KnightKingRingBonus = TaperedEval(KnightKingRingAttackMg, KnightKingRingAttackEg, GamePhase);

    while(WhiteKnightLocations != 0){
        const uint8_t Index = WhiteKnightLocations.pop();
        const chess::Bitboard KnightMoves = chess::attacks::knight(Index);

        // PST + Mobility + King Ring Attack
        WhiteScore += (KnightMoves & BlackKingRing).count() * KnightKingRingBonus;

        WhiteScore += KnightMoves.count() * KnightMobilityBonus;
        WhiteScore += TaperedEval(KnightPSTMg[Index], KnightPSTEg[Index], GamePhase);
    }

    while(BlackKnightLocations != 0){
        const uint8_t RawIndex = BlackKnightLocations.pop();
        const uint8_t PSTIndex = MirrorSquare(RawIndex);
        
        const chess::Bitboard KnightMoves = chess::attacks::knight(RawIndex);

        // PST + Mobility + King Ring Attack
        BlackScore += (KnightMoves & WhiteKingRing).count() * KnightKingRingBonus;
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

    while (WhiteRookLocations != 0) {
        uint8_t Index = WhiteRookLocations.pop();
        WhiteScore += TaperedEval(RookPSTMg[Index], RookPSTEg[Index], GamePhase);
    }

    while (BlackRookLocations != 0) {
        uint8_t RawIndex = BlackRookLocations.pop();
        uint8_t PSTIndex = MirrorSquare(RawIndex);

        BlackScore += TaperedEval(RookPSTMg[PSTIndex], RookPSTEg[PSTIndex], GamePhase);
    }
}

inline void EvaluateQueens(
    const chess::Bitboard& WhiteQueens,
    const chess::Bitboard& BlackQueens,
    const chess::Bitboard& OCC,
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
        uint8_t RawIndex = BlackQueenLocations.pop();
        uint8_t PSTIndex = MirrorSquare(RawIndex);
        BlackScore += TaperedEval(QueenPSTMg[PSTIndex], QueenPSTEg[PSTIndex], GamePhase);
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