#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <vector>

uint8_t GetLsbPosition(uint64_t& bitboard);
void PopLsb(uint64_t& bitboard);

std::vector<uint8_t> GetIndexesFromBitBoard(const chess::Bitboard& Bitboard);
chess::Color OppositeColor(chess::Color color);
int PiecesValue(const chess::PieceType& PieceType);
int TaperedEvaluation(float& weight, float WeightMG, float WeightEG);
chess::Bitboard GetPawnControlledSquares(const chess::Bitboard pawns,const chess::Color color);
chess::Bitboard NorthFill(chess::Bitboard PawnFile);
chess::Bitboard SouthFill(chess::Bitboard PawnFile);

#endif