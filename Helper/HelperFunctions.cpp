#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "HelperFunctions.h"
#include <vector>

chess::Bitboard PopLsb(chess::Bitboard& bitboard) {
    uint64_t bb = bitboard.getBits();
    bb &= bb - 1;
    return chess::Bitboard(bb);
}

std::vector<uint8_t> GetIndexesFromBitBoard(chess::Bitboard& Bitboard){
    std::vector<uint8_t> Indexes;

    for(int i=0;i<64;i++){
        if(Bitboard == 0){break;}
        Indexes.push_back(Bitboard.lsb());
        Bitboard = PopLsb(Bitboard);
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

int TaperedEvaluation(float& weight, int WeightMG, int WeightEG){
    return static_cast<int>(weight * WeightMG + (1 - weight) * WeightEG);
}

chess::Bitboard GetPawnControlledSquares(chess::Bitboard pawns,const chess::Color color){
    std::vector<uint8_t> PawnIndexes = GetIndexesFromBitBoard(pawns);

    chess::Bitboard PawnAttackBitboard = chess::Bitboard(0ULL);

    for(const auto &index : PawnIndexes){
        PawnAttackBitboard |= chess::attacks::pawn(color, index);
    }

    return PawnAttackBitboard;
}

chess::Bitboard NorthFill(chess::Bitboard PawnFile){
    PawnFile |= (PawnFile << 8);
    PawnFile |= (PawnFile << 16);
    PawnFile |= (PawnFile << 32);

    return PawnFile;
}

chess::Bitboard SouthFill(chess::Bitboard PawnFile){
    PawnFile |= (PawnFile >> 8);
    PawnFile |= (PawnFile >> 16);
    PawnFile |= (PawnFile >> 32);

    return PawnFile;
}