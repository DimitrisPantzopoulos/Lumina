#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"

#include "EvalHelp.h"

#include <iostream>
#include <cmath>
#include <map>

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

#define PAWN_VALUE 245
#define KNIGHT_VALUE 915
#define BISHOP_VALUE 961
#define ROOK_VALUE 1608
#define QUEEN_VALUE 3298
#define NOPAWNSHIELD -13
#define VQUEENSCOREMG -7
#define VQUEENSCOREEG 6
#define ISOLATEDPAWN -19
#define DOUBLEDPAWN -37
#define CENTREPAWN 18
#define KNIGHTOUTPOST 52
#define KNIGHTMOBILITY 26
#define ROOKOPENFILE 50
#define ROOKBACKRANK 109
#define ROOKMOBILITYMG 6
#define ROOKMOBILITYEG 7
#define BISHOPOPENFILE 27
#define BISHOPFIXEDPAWNS -20
#define BISHOPMOBILITYMG 9
#define BISHOPMOBILITYEG 11
#define BISHOPPAIR 141

int PiecesValue(const chess::PieceType& type){
    if (type == chess::PieceType::PAWN)        {return PAWN_VALUE;}
    else if (type == chess::PieceType::KNIGHT) {return KNIGHT_VALUE;}
    else if (type == chess::PieceType::BISHOP) {return BISHOP_VALUE;}
    else if (type == chess::PieceType::ROOK)   {return ROOK_VALUE;}
    else if (type == chess::PieceType::QUEEN)  {return QUEEN_VALUE;}

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
    SafetyScore += (FriendPawns & combinedMask).count() * static_cast<int>(weight * NOPAWNSHIELD);

    //Virtual Queen Score 
    SafetyScore += chess::attacks::queen(KSq, occ).count() * static_cast<int>(weight * VQUEENSCOREMG + (1 - weight) * VQUEENSCOREEG);

    //Find how many pieces are threatening the king ring

    return SafetyScore;
}

int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, bool isWhite) {
    constexpr static std::array<int, 7> PawnBonuses = {0, 87, 193, 115, 56, -4, 1};

    static const uint64_t Msquares = 0x1818000000;

    int Score = 0;
    int rank = sq.rank();
    int file = sq.file();

    chess::Bitboard PForward;

    if (isWhite) {
        PForward = chess::Bitboard(0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8));
    } else {
        PForward = chess::Bitboard(0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8));
    }

    // Create a bitboard for the same file
    chess::Bitboard fileMask(0x0101010101010101ULL << file);

    // Create bitboards for the adjacent files
    chess::Bitboard leftFileMask ((file > 0) ? 0x0101010101010101ULL << (file - 1) : 0);
    chess::Bitboard rightFileMask((file < 7) ? 0x0101010101010101ULL << (file + 1) : 0);

    // Combine the masks
    chess::Bitboard combinedMask = fileMask | leftFileMask | rightFileMask;

    // Apply the forward mask to get the relevant bits in front of the pawn
    chess::Bitboard PawnBits = PForward & combinedMask;

    //Check if there are any opposing pawns in the relevant bits (Passed Pawn)
    //Or they are infront of the king which can be used to accellerate an attack on the king (Pawn Storm Heuristic)
    if ((PawnBits & EnemyPawns) == 0) {
        if (isWhite) {
            Score += PawnBonuses[7 - rank];
        } else {
            Score += PawnBonuses[rank];
        }
    }

    chess::Bitboard sameFilePawns(fileMask & FriendPawns.getBits());
    chess::Bitboard currentPawnPosition(1ULL << sq.index());

    // Check if there are any other pawns on the same file (excluding the current pawn)
    if ((sameFilePawns & ~currentPawnPosition) != 0) {
        Score += ISOLATEDPAWN;
    }

    // Check for isolated pawns
    if (((leftFileMask | rightFileMask) & FriendPawns) == 0) {
        Score += DOUBLEDPAWN;
    }
    
    // Check if pawn is in the centre squares 
    if((currentPawnPosition & Msquares) != 0){
        Score += CENTREPAWN;
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
        Score += KNIGHTOUTPOST;
    }

    //Check Knight mobility but disregard squares that pawns are on
    chess::Bitboard KnightMoves = chess::attacks::knight(sq);

    Score += (KnightMoves & ~SCBEP).count() * KNIGHTMOBILITY;

    return Score;
}

int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& oppPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ,float weight ,bool isWhite){
    int Score = 0;

    //Get the file the rook is on and make it into a bitboard
    int file = sq.file();

    uint64_t fileMask = 0x0101010101010101ULL << file;

    //Check if the rook is on a open file
    if(((oppPawns | FriendPawns) & fileMask) == 0){
        Score += ROOKOPENFILE;
    }

    if(isWhite && sq.rank() == chess::Rank::RANK_7){
        Score += ROOKBACKRANK;
    }else if(!isWhite && sq.rank() == chess::Rank::RANK_2){
        Score += ROOKBACKRANK;
    }

    chess::Bitboard RookMoves = chess::attacks::rook(sq, occ);
    
    Score += static_cast<int>(RookMoves.count() * (weight * ROOKMOBILITYMG + (1.0f - weight) * ROOKMOBILITYEG));

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
        Score += BISHOPOPENFILE;
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

    //Fixed Pawns are harder to get rid of so we should make them twice as bad
    Score += NoOfFixedPawns * BISHOPFIXEDPAWNS;

    Score += static_cast<int>((BishopBitBoard & ~EnemyPawnsSq).count() * (weight * BISHOPMOBILITYMG + (1.0f - weight) * BISHOPMOBILITYEG));;

    return Score;
}

int EvaluateMobilityArea(const chess::Board& board, chess::Bitboard& FriendlyPawns, chess::Bitboard& EnemyPawnAttacks, chess::Color EnemyColor){
    chess::Bitboard EnemyKingIndex(1ULL << board.kingSq(EnemyColor).index());

    chess::Bitboard MobilityArea(0xFFFFFFFFFFFFFFFFULL);

    if (EnemyColor == chess::Color::WHITE) {
        chess::Bitboard BlockedPawns = FriendlyPawns & (FriendlyPawns << 8);
        MobilityArea &= ~BlockedPawns;
    } else {
        chess::Bitboard BlockedPawns = FriendlyPawns & (FriendlyPawns >> 8);
        MobilityArea &= ~BlockedPawns;
    }

    MobilityArea &= ~FriendlyPawns;
    MobilityArea &= ~EnemyPawnAttacks;
    MobilityArea &= ~EnemyKingIndex;

    return MobilityArea.count();
}