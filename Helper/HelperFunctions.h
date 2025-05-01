#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library\include\chess.hpp"

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

<<<<<<< Updated upstream
<<<<<<< Updated upstream
int PiecesValue(const chess::PieceType& PieceType);
int TaperedEvaluation(float& weight, int WeightMG, int WeightEG);
=======
inline double TaperedEvaluation(const double& weight, const double WeightMG, const double WeightEG){
    return static_cast<int>(weight * WeightMG + (1 - weight) * WeightEG);
=======
inline int TaperedEvaluation(const float& weight, const int WeightMG, const int WeightEG){
    return static_cast<int>(weight * static_cast<float>(WeightMG) + (1 - weight) * static_cast<float>(WeightEG));
>>>>>>> Stashed changes
}
>>>>>>> Stashed changes

chess::Bitboard GetPawnControlledSquares(const chess::Bitboard& pawns, const chess::Color color);

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

#endif