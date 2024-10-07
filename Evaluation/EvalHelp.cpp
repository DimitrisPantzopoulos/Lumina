#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"

#include "EvalHelp.h"
#include <iostream>

chess::Bitboard GetPawnControlledSquares(const chess::Bitboard pawns,const chess::Color color){
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

#define PAWN_VALUE 342
#define KNIGHT_VALUE 998
#define BISHOP_VALUE 1127
#define ROOK_VALUE 1717
#define QUEEN_VALUE 3590
#define NOPAWNSHIELD -13
#define VQUEENSCOREMG -12
#define VQUEENSCOREEG 1
constexpr int PawnBonuses[] = {0, 441, 327, 172, 81, 33, 33};
#define ISOLATEDPAWN -9
#define DOUBLEDPAWN -23
#define CENTREPAWN 18
#define KNIGHTOUTPOST 105
#define KNIGHTMOBILITY 28
#define ROOKOPENFILE 67
#define ROOKSEMIOPENFILE 19
#define ROOKBACKRANK 68
#define ROOKMOBILITYMG 10
#define ROOKMOBILITYEG 11
#define BISHOPOPENFILE 22
#define BISHOPSEMIOPENFILE -6
#define BISHOPNONFIXEDPAWNS -4
#define BISHOPFIXEDPAWNS -11
#define BISHOPMOBILITYMG 14
#define BISHOPMOBILITYEG 16
#define SCORE_OPEN_FILE 59
#define SCORE_SEMI_OPEN_FILE 8
#define SCORE_OPEN_DIAGONAL 25

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
    SafetyScore += (FriendPawns & combinedMask).count() * static_cast<int>(weight * -17);

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

    uint64_t sameFilePawns = fileMask & FriendPawns.getBits();
    uint64_t currentPawnPosition = 1ULL << sq.index();

    // Check if there are any other pawns on the same file (excluding the current pawn)
    if ((sameFilePawns & ~currentPawnPosition) != 0) {
        Score += -9;
    }

    // Check for isolated pawns
    if (((leftFileMask | rightFileMask) & FriendPawns.getBits()) == 0) {
        Score += -4;
    }
    
    //check if pawn is in the centre squares 
    if((currentPawnPosition & Msquares) != 0){
        Score += 17;
    }

    
    return Score;
}

int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, bool isWhite){
    //We want Knights to be on outposts in the middle so they can control as many squares as possible
    //and basically harrass the other side
    int file = sq.file();
    int rank = sq.rank();

    //Get the bits behind one rank of the knight and in front of it
    uint64_t KForward;
    uint64_t KBackward;

    if (isWhite) {
        KForward = (rank > 0) ? 0xFFFFFFFFFFFFFFFFULL << ((rank+1) * 8) : 0;
        KBackward = (sq.index() >= 9 ? 0x5ULL << (sq.index() - 9) : 0) & ~0x8181818181818181;
    }else {
        KForward = (rank < 7) ? 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8) : 0;
        KBackward = (sq.index() <= 56 ? 0x5ULL << (sq.index() + 7) : 0) & ~0x8181818181818181;
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

    Score += (KnightMoves & ~SCBEP).count() * 15;

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

int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ, const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite){
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
    Score += (NoOfPawns - NoOfFixedPawns) * -2;
    
    //Fixed Pawns are harder to get rid of so we should make them twice as bad
    Score += NoOfFixedPawns * -2;

    Score += (BishopBitBoard & ~EnemyPawnsSq).count() * static_cast<int>(weight * 10 + (1.0f - weight) * 12);

    return Score;
}

int EvaluateQueen(const chess::Square &sq, chess::Bitboard& occ, chess::Bitboard& FriendPawns, chess::Bitboard& EnemyPawns, chess::Square Ksq, bool isWhite) {
    int Score = 0;
    int rank = sq.rank();
    int file = sq.file();

    chess::Bitboard QueenDiagonalBitBoard = chess::attacks::bishop(sq, occ);
    chess::Bitboard QueenHorizontalBitboard(0x0101010101010101ULL << file);

    chess::Bitboard CombinedMask = FriendPawns | EnemyPawns;

    //Check if bishop controls a open diagonal
    //The reason for < 2 is because the bishop can only control max 2 open diagonals if i didnt do this
    //it could control a open diagonal and not be rewarded for it
    if((CombinedMask & QueenDiagonalBitBoard).count() < 2){
        Score += 50;
    }

    //Check if the queen is on a open/semi open file
    if(((EnemyPawns | FriendPawns) & QueenHorizontalBitboard) == 0){
        Score += 50;
    }else if((EnemyPawns & QueenHorizontalBitboard) == 0){
        Score += 20;
    }

    if(isWhite && sq.rank() == chess::Rank::RANK_7){
        Score += 25;
    }else if(!isWhite && sq.rank() == chess::Rank::RANK_2){
        Score += 25;
    }

    return Score;
}