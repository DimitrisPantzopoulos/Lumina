#include "..\ChessLib\chess-library\include\chess.hpp"
#include "HelperFunctions.h"
#include <vector>

int PiecesValue(const chess::PieceType& PieceType){
    if (PieceType == chess::PieceType::PAWN)        {return 267;}
    else if (PieceType == chess::PieceType::KNIGHT) {return 958;}
    else if (PieceType == chess::PieceType::BISHOP) {return 991;}
    else if (PieceType == chess::PieceType::ROOK)   {return 1642;}
    else if (PieceType == chess::PieceType::QUEEN)  {return 3361;}
    return 0;
}

int TaperedEvaluation(float& weight, int WeightMG, int WeightEG){
    return static_cast<int>(weight * WeightMG + (1 - weight) * WeightEG);
}

chess::Bitboard GetPawnControlledSquares(const chess::Bitboard& pawns, const chess::Color color){
    uint16_t PawnIndexes = pawns.getBits();

    chess::Bitboard PawnAttackBitboard(0ULL);

    while (PawnIndexes) {
        int Index = __builtin_ctzll(PawnIndexes);
        
        PawnAttackBitboard |= chess::attacks::pawn(color, Index);

        PawnIndexes &= PawnIndexes - 1;
    }

    return PawnAttackBitboard;
}
