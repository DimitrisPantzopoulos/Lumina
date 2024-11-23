#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <vector>

uint8_t GetLsbPosition(uint64_t& bitboard);
int PiecesValue(const chess::PieceType& PieceType);
int TaperedEvaluation(float& weight, int WeightMG, int WeightEG);

std::vector<uint8_t> GetIndexesFromBitBoard(chess::Bitboard& Bitboard);

chess::Color OppositeColor(chess::Color color);
chess::Bitboard PopLsb(uint64_t& bitboard);
chess::Bitboard GetPawnControlledSquares(chess::Bitboard pawns,const chess::Color color);
chess::Bitboard NorthFill(chess::Bitboard PawnFile);
chess::Bitboard SouthFill(chess::Bitboard PawnFile);

#endif