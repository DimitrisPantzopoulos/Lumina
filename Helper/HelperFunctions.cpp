#include "..\ChessLib\chess-library\include\chess.hpp"
#include "HelperFunctions.h"
#include <vector>

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
