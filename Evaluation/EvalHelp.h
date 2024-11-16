#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"

chess::Bitboard GetPawnControlledSquares(const chess::Bitboard pawns,const chess::Color color);

chess::Bitboard NorthFill(chess::Bitboard PawnFile);
chess::Bitboard SouthFill(chess::Bitboard PawnFile);

float PiecesValueEval(const chess::PieceType& PieceType, float weight);
float SafetyScore(const chess::Square &KSq,const chess::Bitboard& occ, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
float EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
float EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite);
float EvaluateRooks(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ, float weight, bool isWhite);
float EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ ,const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite);
float EvaluateQueen(const chess::Board& board, const chess::Bitboard& EnemyPawns, const chess::Bitboard occ, const chess::Square &sq, const chess::Color EnemyColor, float weight);
#endif