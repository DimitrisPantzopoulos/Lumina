#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include <vector>

int PiecesValue(const chess::PieceType& PieceType);
int TaperedEvaluation(float& weight, int WeightMG, int WeightEG);

chess::Bitboard GetPawnControlledSquares(const chess::Bitboard& pawns, const chess::Color color);

#endif