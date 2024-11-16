#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <vector>

uint8_t GetLsbPosition(uint64_t& bitboard);
void PopLsb(uint64_t& bitboard);

std::vector<uint8_t> GetIndexesFromBitBoard(const chess::Bitboard& Bitboard);
chess::Color OppositeColor(chess::Color color);
int PiecesValue(const chess::PieceType& PieceType);
float TaperedEvaluation(float& weight, float WeightMG, float WeightEG);
#endif