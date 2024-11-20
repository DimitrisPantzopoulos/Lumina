#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "HelperFunctions.h"
#include <vector>

uint8_t GetLsbPosition(uint64_t& bitboard) {
    return __builtin_ctzll(bitboard);
}

void PopLsb(uint64_t& bitboard) {
    bitboard &= bitboard - 1;
}

std::vector<uint8_t> GetIndexesFromBitBoard(const chess::Bitboard& Bitboard){
    uint64_t BB = Bitboard.getBits();
    std::vector<uint8_t> Indexes;

    for(int i=0;i<64;i++){
        if(BB == 0){
            break;
        }

        Indexes.push_back(GetLsbPosition(BB));

        PopLsb(BB);
    }

    return Indexes;
}

chess::Color OppositeColor(chess::Color color){
    return color == chess::Color::WHITE ? chess::Color::BLACK : chess::Color::WHITE;
}

int PiecesValue(const chess::PieceType& PieceType){
    if (PieceType == chess::PieceType::PAWN)        {return 267;}
    else if (PieceType == chess::PieceType::KNIGHT) {return 958;}
    else if (PieceType == chess::PieceType::BISHOP) {return 991;}
    else if (PieceType == chess::PieceType::ROOK)   {return 1642;}
    else if (PieceType == chess::PieceType::QUEEN)  {return 3361;}
    return 0;
}

int TaperedEvaluation(float& weight, float WeightMG, float WeightEG){
    return static_cast<int>(weight * WeightMG + (1 - weight) * WeightEG);
}


