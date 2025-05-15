#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "..\ChessLib\chess.hpp"
#include <vector>

constexpr int MAX_PHASE = 24;

inline chess::Bitboard NorthFill(chess::Bitboard BB){
    BB |= (BB << 8);
    BB |= (BB << 16);
    BB |= (BB << 32);
    return BB;
}

inline chess::Bitboard SouthFill(chess::Bitboard BB){
    BB |= (BB >> 8);
    BB |= (BB >> 16);
    BB |= (BB >> 32);
    return BB;
}

inline int CalculateGamePhase(const chess::Board& board){
    constexpr int KnightWeight = 1;
    constexpr int BishopWeight = 1;
    constexpr int RookWeight  = 2;
    constexpr int QueenWeight = 4;

    int Phase = 0;

    Phase += board.pieces(chess::PieceType::KNIGHT).count() * KnightWeight;
    Phase += board.pieces(chess::PieceType::BISHOP).count() * BishopWeight;
    Phase += board.pieces(chess::PieceType::ROOK  ).count() * RookWeight;
    Phase += board.pieces(chess::PieceType::QUEEN ).count() * QueenWeight;

    return Phase;
}

inline int TaperedEval(int MgWeight, int EgWeight, int Phase) {
    return (MgWeight * Phase + EgWeight * (MAX_PHASE - Phase)) / MAX_PHASE;
}

inline int CalculateExtension(const chess::Board& board, int &Extensions, const chess::Move& move) {
    int Extension = 0;

    chess::PieceType Type = board.at(move.from()).type();
    chess::Rank MoveRank = move.to().rank();

    if (Extensions < 16) {
        Extension += board.inCheck() ? 1 : 0;
        Extension += Type == chess::PieceType::PAWN && (MoveRank == chess::Rank::RANK_2 || MoveRank == chess::Rank::RANK_7);
    }

    return Extension;
}

inline int MirrorSquare(int sq) {
    return ((7 - (sq / 8)) * 8) + (sq % 8);
}

#endif