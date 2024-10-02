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

