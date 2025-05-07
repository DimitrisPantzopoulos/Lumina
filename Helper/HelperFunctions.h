#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include <vector>

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
    return static_cast<int>(weight * WeightMG + (1 - weight) * WeightEG);
}

inline chess::Bitboard GetPawnControlledSquares(const chess::Bitboard& pawns, const chess::Color color){
    chess::Bitboard PawnIndexes = pawns;
    chess::Bitboard PawnAttackBitboard(0ULL);

    while (PawnIndexes != 0) {
        chess::Square Index(PawnIndexes.lsb());
        PawnAttackBitboard |= chess::attacks::pawn(color, Index);
        PawnIndexes &= PawnIndexes.pop();
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

#endif