#ifndef EVALHELP_H
#define EVALHELP_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"

chess::Bitboard GetPawnControlledSquares(const chess::Bitboard pawns,const chess::Color color);

chess::Bitboard NorthFill(chess::Bitboard PawnFile);
chess::Bitboard SouthFill(chess::Bitboard PawnFile);

int SafetyScore(const chess::Square &KSq,const chess::Bitboard& occ, const chess::Bitboard &FriendPawns, float weight, bool isWhite);
int PiecesValue(const chess::PieceType& type);

int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &oppPawns, const chess::Bitboard &FriendPawns, bool isWhite);
int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, bool isWhite);
int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ,float weight, bool isWhite);
int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ ,const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite);
int EvaluateQueen(const chess::Board& board, const chess::Square &sq, chess::Bitboard& occ, chess::Bitboard& EnemyPawns, chess::Square Ksq, bool isWhite);

#endif