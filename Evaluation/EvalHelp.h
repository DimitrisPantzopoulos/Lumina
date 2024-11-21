#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"

int PiecesValueEval(const chess::PieceType& PieceType, float weight);
int SafetyScore(const chess::Square &KSq,const chess::Bitboard& occ, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite);
int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ, float weight, bool isWhite);
int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ ,const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite);
int EvaluateQueen(const chess::Square &sq, const chess::Board& board, const chess::Bitboard& EnemyPawns, const chess::Bitboard occ, const chess::Color EnemyColor, float weight);
#endif