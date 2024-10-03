#include "EvalHelp.h"
#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <iostream>

int PiecesValue(const chess::PieceType& type){
    if (type == chess::PieceType::PAWN)        {return 226;}
    else if (type == chess::PieceType::KNIGHT) {return 664;}
    else if (type == chess::PieceType::BISHOP) {return 725;}
    else if (type == chess::PieceType::ROOK)   {return 1139;}
    else if (type == chess::PieceType::QUEEN)  {return 2331;}
    else if (type == chess::PieceType::KING)   {return 0; }

    return 0;
}

int SafetyScore(const chess::Square &KSq, const chess::Bitboard& occ ,const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    int file = KSq.file();
    int rank = KSq.rank();

    uint64_t KForward;

    if (isWhite) {
        KForward = 0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8);
    } else {
        KForward = 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8);
    }

    //Check if King on open file
    uint64_t fileMask = 0x0101010101010101ULL << file;

    // Create bitboards for the adjacent files
    uint64_t leftFileMask = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
    uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

    // Combine the masks
    uint64_t combinedMask = (fileMask | leftFileMask | rightFileMask) & KForward;

    int SafetyScore = 0;
    
    //See if the king has a pawn shield
    if((FriendPawns.getBits() & combinedMask) == 0){
        SafetyScore += static_cast<int>(weight * -51);
    }

    //Virtual Queen Score 
    SafetyScore += chess::attacks::queen(KSq, occ).count() * static_cast<int>(weight * (-11) + (1 - weight) * 2);

    return SafetyScore;
}

int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &oppPawns, const chess::Bitboard &FriendPawns, bool isWhite) {
    constexpr static std::array<int, 7> PawnBonuses = {0, 271, 207, 122, 65, 36, 30};
    static const uint64_t Msquares = 0x1818000000;

    int Score = 0;
    int rank = sq.rank();
    int file = sq.file();
    int index = sq.index();

    uint64_t FriendlyPawns = FriendPawns.getBits();

    uint64_t PForward;

    if (isWhite) {
        PForward = 0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8);
    } else {
        PForward = 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8);
    }

    // Create a bitboard for the same file
    uint64_t fileMask = 0x0101010101010101ULL << file;

    // Create bitboards for the adjacent files
    uint64_t leftFileMask = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
    uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

    // Combine the masks
    uint64_t combinedMask = fileMask | leftFileMask | rightFileMask;

    // Apply the forward mask to get the relevant bits in front of the pawn
    uint64_t PawnBits = PForward & combinedMask;

    // Check if there are any opposing pawns in the relevant bits (Passed Pawn)
    //Or they are infront of the king which can be used to accellerate an attack on the king (Pawn Storm Heuristic)
    if ((PawnBits & oppPawns.getBits()) == 0) {
        if (isWhite) {
            Score += PawnBonuses[7 - rank];
        } else {
            Score += PawnBonuses[rank];
        }
    }

    uint64_t sameFilePawns = fileMask & FriendlyPawns;
    uint64_t currentPawnPosition = 1ULL << sq.index();

    // Check if there are any other pawns on the same file (excluding the current pawn)
    if ((sameFilePawns & ~currentPawnPosition) != 0) {
        Score -= 9;
    }

    // Check for isolated pawns
    if (((leftFileMask | rightFileMask) & FriendlyPawns) == 0) {
        Score -= 4;
    }
    
    //check if pawn is in the centre squares 
    if((currentPawnPosition & Msquares) != 0){
        Score += 17;
    }

    //Check if a pawn is a phalanx pawn
    uint64_t LeftSquare = (file > 0) ? (currentPawnPosition << 1) : 0;
    uint64_t RightSquare = (file < 7) ? (currentPawnPosition >> 1) : 0;

    if ((FriendlyPawns & LeftSquare) != 0) {
        Score += 7;
    }

    if((FriendlyPawns & RightSquare) != 0){
        Score += 7;
    }

    //Check if a pawn is connected
    uint64_t DownLeft, DownRight;

    if (isWhite) {
        DownLeft = (currentPawnPosition >> 9) & ~0x0101010101010101ULL;  // Prevent wrap-around on file 'a'
        DownRight = (currentPawnPosition >> 7) & ~0x8080808080808080ULL; // Prevent wrap-around on file 'h'
    }else {
        DownLeft = (currentPawnPosition << 7) & ~0x0101010101010101ULL;  // Prevent wrap-around on file 'a'
        DownRight = (currentPawnPosition << 9) & ~0x8080808080808080ULL; // Prevent wrap-around on file 'h'
    }

    if ((FriendlyPawns & DownLeft) != 0 || (FriendlyPawns & DownRight) != 0) {
        Score += 4;
    }
    
    return Score;
}

int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, bool isWhite){
    //We want Knights to be on outposts in the middle so they can control as many squares as possible
    //and basically harrass the other side
    int file = sq.file();
    int rank = sq.rank();
    int index = sq.index();
    //Get the bits behind one rank of the knight and in front of it
    uint64_t KForward;
    uint64_t KBackward;

    if (isWhite) {
        KForward = (rank > 0) ? 0xFFFFFFFFFFFFFFFFULL << ((rank+1) * 8) : 0;
        KBackward = (index >= 9) ? 0x5ULL << (index - 9) : 0;
    } else {
        KForward = (rank < 7) ? 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8) : 0;
        KBackward = (index <= 56) ? 0x5ULL << (index + 7) : 0;
    }
    
    // Create bitboards for the adjacent files
    uint64_t leftFileMask = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
    uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

    uint64_t CombinedMask = leftFileMask | rightFileMask;

    //Apply the forward mask to get the relevant bits in front and behind the knight which creates like an X Shape
    uint64_t KnightBits = KForward & CombinedMask;

    int Score = 0;

    //See if a knight is on a outpost
    if (((KnightBits & oppPawns.getBits()) == 0) && ((KBackward & FriendPawns.getBits()) != 0)) {
        Score += 74;
    }

    //Check Knight mobility but disregard squares that pawns are on
    chess::Bitboard KnightMoves = chess::attacks::knight(sq);

    Score += (KnightMoves & ~oppPawns).count() * 15;

    return Score;
}

int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ,float weight ,bool isWhite){
    int Score = 0;

    //Get the file the rook is on and make it into a bitboard
    int file = sq.file();

    uint64_t fileMask = 0x0101010101010101ULL << file;

    //Check if the rook is on a open file
    if(((oppPawns | FriendPawns) & fileMask) == 0){
        Score += 47;
    }else if((oppPawns & fileMask) == 0){
        Score += 15;
    }

    if(isWhite && sq.rank() == chess::Rank::RANK_7){
        Score += 42;
    }else if(!isWhite && sq.rank() == chess::Rank::RANK_2){
        Score += 42;
    }

    chess::Bitboard RookMoves = chess::attacks::rook(sq, occ);
    
    Score += RookMoves.count() * static_cast<int>(weight * 6 + (1.0f - weight) * 7);

    return Score;
}

int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ ,const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, float weight, bool isWhite){
    static const chess::Bitboard LIGHT_SQUARES= chess::Bitboard(0x55AA55AA55AA55AAULL);
    static const chess::Bitboard DARK_SQUARES = chess::Bitboard(0xAA55AA55AA55AA55ULL);

    chess::Bitboard BishopBitBoard = chess::attacks::bishop(sq, occ);

    int rank = sq.rank();

    //Create a combined mask which has both friendly and opposition pawns
    chess::Bitboard CombinedMask = FriendPawns | oppPawns;

    //Create a forwards mask to delete all behind moves
    chess::Bitboard BForward;

    if (isWhite) {
        BForward = 0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8);
    } else {
        BForward = 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8);
    }

    //Combine Backwards and BishopBitboard to have only the forwards moves
    int Score = 0;

    //Check if bishop controls a open diagonal
    //The reason for < 2 is because the bishop can only control max 2 open diagonals if i didnt do this
    //it could control a open diagonal and not be rewarded for it
    if((CombinedMask & BishopBitBoard).count() < 2){
        Score += 32;
    }else if((oppPawns & BishopBitBoard & BForward).count() < 2){
        Score += 11;
    }

    // //Detect Bad Bishop
    int NoOfFixedPawns;
    int NoOfPawns;

    //Is bishop light or dark squared?
    if((chess::Bitboard(1ULL << sq.index()) & LIGHT_SQUARES) != 0){
        //If its a light squared bishop

        //Find how many total pawns there are blocking the bishop
        chess::Bitboard WhiteSquaredPawns = (LIGHT_SQUARES & FriendPawns) & BForward;
        NoOfPawns = (WhiteSquaredPawns).count();

        //Find out how many Fixed pawns Pawns that dont move are in the position
        if(isWhite){
            NoOfFixedPawns = ((WhiteSquaredPawns << 8) & oppPawns).count();
        }else{
            NoOfFixedPawns = ((WhiteSquaredPawns >> 8) & oppPawns).count();
        }

    }else{
        //Find how many total pawns there are blocking the bishop
        chess::Bitboard BlackSquaredPawns = (DARK_SQUARES & FriendPawns) & BForward;
        NoOfPawns = (BlackSquaredPawns).count();

        //Find out how many Fixed pawns Pawns that dont move are in the position
        if(isWhite){
            NoOfFixedPawns = ((BlackSquaredPawns << 8) & oppPawns).count();
        }else{
            NoOfFixedPawns = ((BlackSquaredPawns >> 8) & oppPawns).count();
        }
    }

    //Use the forward mobility to calulate what a punishment should be for this closed position
    //Calculate the total number of non fixed pawns in the position
    Score -= (NoOfPawns - NoOfFixedPawns) * 2;
    
    //Fixed Pawns are harder to get rid of so we should make them twice as bad
    Score -= NoOfFixedPawns * -2;

    Score += BishopBitBoard.count() * static_cast<int>(weight * 10 + (1.0f - weight) * 12);

    return Score;
}

//USED FOR TESTING BITBOARD STUFF
// void PrintBitBoard(uint64_t bitboard) {
//     std::cout << "Bitboard:\n";
//     for (int rank = 7; rank >= 0; --rank) {
//         for (int file = 0; file < 8; ++file) {
//             // Calculate the bit position
//             uint64_t bit = 1ULL << (rank * 8 + file);
//             // Print '1' if the bit is set, otherwise '0'
//             std::cout << ((bitboard & bit) ? '1' : '0') << ' ';
//         }
//         std::cout << '\n';
//     }
// }

// void GetBitBoard(bool isWhite, chess::Square sq){
//     int file = sq.file();
//     int rank = sq.rank();

//     //Get the bits behind one rank of the knight and in front of it
//     uint64_t KForward;
//     uint64_t KBackward;

//     if (isWhite) {
//         KForward = (rank > 0) ? 0xFFFFFFFFFFFFFFFFULL << ((rank+1) * 8) : 0;
//         KBackward = (sq.index() > 9) ? 0x5ULL << (sq.index() - 9) : 0;
//     } else {
//         KForward = (rank < 7) ? 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8) : 0;
//         KBackward = (sq.index() < 56) ? 0x5ULL << (sq.index() + 7) : 0;
//     }
    
//     uint64_t KFB = KForward | KBackward;
    
//     // Create bitboards for the adjacent files
//     uint64_t leftFileMask = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
//     uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

//     uint64_t CombinedMask = leftFileMask | rightFileMask;

//     //Apply the forward mask to get the relevant bits in front and behind the knight which creates like an X Shape
//     uint64_t KnightBits = KFB & CombinedMask;

//     PrintBitBoard(KnightBits);
// }
