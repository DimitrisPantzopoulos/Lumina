#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\EvaluationFeatures\Features.h"

inline uint64_t NorthFill(uint64_t BB){
    BB |= (BB << 8);
    BB |= (BB << 16);
    BB |= (BB << 32);
    return BB;
}

inline uint64_t SouthFill(uint64_t BB){
    BB |= (BB >> 8);
    BB |= (BB >> 16);
    BB |= (BB >> 32);
    return BB;
}

inline int TaperedEvaluation(const float& weight, const int WeightMG, const int WeightEG){
    return static_cast<int>(weight * static_cast<float>(WeightMG) + (1 - weight) * static_cast<float>(WeightEG));
}

inline chess::Bitboard GetPawnControlledSquares(const chess::Bitboard& pawns, const chess::Color color){
    uint16_t PawnIndexes = pawns.getBits();

    chess::Bitboard PawnAttackBitboard(0ULL);

    while (PawnIndexes) {
        int Index = __builtin_ctzll(PawnIndexes);
        
        PawnAttackBitboard |= chess::attacks::pawn(color, Index);

        PawnIndexes &= PawnIndexes - 1;
    }

    return PawnAttackBitboard;
}

inline int CalculateExtension(const chess::Board& board, int &Extensions, const chess::Move& move) {
    int Extension = 0;

    chess::PieceType Type = board.at(move.from()).type();
    chess::Rank MoveRank = move.to().rank();

    if (Extensions < 16) {
        Extension += board.inCheck() ? 1 : 0;
        Extension += Type == chess::PieceType::PAWN && (MoveRank == chess::Rank::RANK_2 || MoveRank == chess::Rank::RANK_7);
    }

    return Extension;
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

#endif