#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"
#include "..\EvaluationFeatures\Features.h"

inline int EvaluatePawn(
    const chess::Square& Sq,
    const float EndgameWeight,
    const bool Color,
    int PSTIndex
)
{   
    int Score = 0;
    int Rank = Sq.rank();
    Rank = Color ? Rank : (7 - Rank);
    int SquareIndex = PSTIndex;
    
    // Pawn Bonuses + Pawn Value + Pawn PST
    int color = Color ? 0 : 1;

    Score += TaperedEvaluation(EndgameWeight, PawnBonuses[Rank], PawnBonusesEG[Rank]);
    Score += TaperedEvaluation(EndgameWeight, PAWN_VALUE_MG, PAWN_VALUE_EG);
    Score += TaperedEvaluation(EndgameWeight, mg_pawn_table[SquareIndex], eg_pawn_table[SquareIndex]);

    return Score;
}

inline int EvaluateKnight(
    const chess::Square&   Sq,
    const chess::Bitboard& EnemyPawnThreats,
    const float EndgameWeight,
    const int PSTIndex,
    const bool Color
)
{   
    int Score = 0;
    int mobility = (chess::attacks::knight(Sq) & ~EnemyPawnThreats).count();;

    Score += mobility * TaperedEvaluation(EndgameWeight, KNIGHTMOBILITY_MG, KNIGHTMOBILITY_EG);
    Score += TaperedEvaluation(EndgameWeight, KNIGHT_VALUE_MG, KNIGHT_VALUE_EG);
    Score += mg_knight_table[PSTIndex];

    return Score;
}

inline int EvaluateBishop(
    const chess::Square &Sq, 
    const chess::Bitboard& occ, 
    const float EndgameWeight,
    const int PSTIndex,
    const bool Color
)
{
    int Score = 0;

    // Bishop mobility = number of squares attacked
    int mobility = chess::attacks::bishop(Sq, occ).count();

    Score += mobility * TaperedEvaluation(EndgameWeight, BISHOPMOBILITY_MG, BISHOPMOBILITY_EG);
    Score += TaperedEvaluation(EndgameWeight, BISHOP_VALUE_MG, BISHOP_VALUE_EG);
    Score += mg_bishop_table[PSTIndex];
    return Score;
}

inline int EvaluateRook(
    const chess::Square &Sq, 
    const chess::Bitboard& occ, 
    const float EndgameWeight,
    const int PSTIndex,
    const bool Color
)
{
    int Score = 0;
    int mobility = chess::attacks::rook(Sq, occ).count();

    Score += mobility * TaperedEvaluation(EndgameWeight, ROOKMOBILITY_MG, ROOKMOBILITY_EG);
    Score += TaperedEvaluation(EndgameWeight, ROOK_VALUE_MG, ROOK_VALUE_EG);
    Score += mg_rook_table[PSTIndex];

    return Score;
}


inline int EvaluateQueen(
    const chess::Square &Sq,
    const float EndgameWeight,
    const int PSTIndex,
    const bool Color
)
{
    int Score = 0;

    Score += TaperedEvaluation(EndgameWeight, QUEEN_VALUE_MG, QUEEN_VALUE_EG);
    Score += mg_queen_table[PSTIndex];

    return Score;
}

inline int EvaluateKing(
    const chess::Square &Sq,
    const chess::Bitboard& FriendlyPawns,
    const chess::Bitboard& occ,
    const float EndgameWeight,
    const int PSTIndex,
    const bool Color
)
{   
    int File = Sq.file();
    int Score = 0;

    constexpr uint64_t NOT_HFILE      = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE      = ~0x0101010101010101ULL;
    

    int VQUEEN = chess::attacks::queen(Sq, occ).count();

    uint64_t KingMaskIndex = 1ULL << Sq.index();
    uint64_t KingForwardMask = Color ? NorthFill(KingMaskIndex) : SouthFill(KingMaskIndex);
    uint64_t LeftMask     = (KingForwardMask & NOT_AFILE) << 1;
    uint64_t RightMask    = (KingForwardMask & NOT_HFILE) >> 1;
    uint64_t CombinedMask = LeftMask | KingForwardMask | RightMask;

    int PawnShieldCount = (FriendlyPawns & CombinedMask).count();

    Score += PawnShieldCount * TaperedEvaluation(EndgameWeight, NOPAWNSHIELD_MG, NOPAWNSHIELD_EG);
    Score += VQUEEN * TaperedEvaluation(EndgameWeight, VQUEENSCOREMG, VQUEENSCOREEG);
    Score += TaperedEvaluation(EndgameWeight, mg_king_table[PSTIndex], eg_king_table[PSTIndex]);

    return Score;
}

void EvaluatePawns(
    const chess::Bitboard& WhitePawns, const chess::Bitboard& BlackPawns, 
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
);

void EvaluateKnights(
    const chess::Bitboard& WhiteKnights,            const chess::Bitboard& BlackKnights,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares, const chess::Bitboard& BlackPawnsAttackSquares,
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
);

void EvaluateRooks(
    const chess::Bitboard& WhiteRooks,              const chess::Bitboard& BlackRooks,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
);

void EvaluateBishops(
    const chess::Bitboard& WhiteBishops,            const chess::Bitboard& BlackBishops,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares, const chess::Bitboard& BlackPawnsAttackSquares,
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
);
#endif