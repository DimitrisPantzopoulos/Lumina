#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"

constexpr int PAWN_VALUE_MG = 286;
constexpr int PAWN_VALUE_EG = 319;

constexpr int KNIGHT_VALUE_MG = 975;
constexpr int KNIGHT_VALUE_EG = 867;

constexpr int BISHOP_VALUE_MG = 952;
constexpr int BISHOP_VALUE_EG = 981;

constexpr int ROOK_VALUE_MG = 1458;
constexpr int ROOK_VALUE_EG = 1716;

constexpr int QUEEN_VALUE_MG = 3412;
constexpr int QUEEN_VALUE_EG = 3151;

inline int PiecesValueEval(const int& PieceType, float weight) {
    switch (static_cast<int>(PieceType)) {
        case 0: // PAWN
            return TaperedEvaluation(weight, PAWN_VALUE_MG, PAWN_VALUE_EG);
        case 1: // KNIGHT
            return TaperedEvaluation(weight, KNIGHT_VALUE_MG, KNIGHT_VALUE_EG);
        case 2: // BISHOP
            return TaperedEvaluation(weight, BISHOP_VALUE_MG, BISHOP_VALUE_EG);
        case 3: // ROOK
            return TaperedEvaluation(weight, ROOK_VALUE_MG, ROOK_VALUE_EG);
        case 4: // QUEEN
            return TaperedEvaluation(weight, QUEEN_VALUE_MG, QUEEN_VALUE_EG);
        default:
            return  0;
    }
}

inline int PiecesValue(const int& PieceType){
    switch (PieceType){
        case 0: //PAWN
            return PAWN_VALUE_MG;
        case 1:
            return KNIGHT_VALUE_MG;
        case 2:
            return BISHOP_VALUE_MG;
        case 3:
            return ROOK_VALUE_MG;
        case 4:
            return QUEEN_VALUE_MG;
        default:
            return 0;

    }
}

int SafetyScore(const chess::Square &KSq,const chess::Bitboard& occ, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite);
int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ, float weight, bool isWhite);
int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ ,const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite);
int EvaluateQueen(const chess::Square &sq, const chess::Board& board, const chess::Bitboard& EnemyPawns, const chess::Bitboard occ, const chess::Color EnemyColor, float weight);
#endif