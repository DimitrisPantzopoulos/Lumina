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

#define PAWN_VALUE 226
#define KNIGHT_VALUE 664
#define BISHOP_VALUE 725
#define ROOK_VALUE 1139
#define QUEEN_VALUE 2331

#define NOPAWNSHIELD -17
#define VQUEENSCOREMG -11
#define VQUEENSCOREEG 2

//constexpr int PawnBonuses[] = {0, 271, 207, 122, 65, 36, 30};

#define ISOLATEDPAWN -9
#define DOUBLEDPAWN -4
#define CENTREPAWN 17

#define KNIGHTOUTPOST 74
#define KNIGHTMOBILITY 15

#define ROOKOPENFILE 47
#define ROOKSEMIOPENFILE 15
#define ROOKBACKRANK 42
#define ROOKMOBILITYMG 6
#define ROOKMOBILITYEG 7

#define BISHOPOPENFILE 32
#define BISHOPSEMIOPENFILE 11
#define BISHOPNONFIXEDPAWNS -2
#define BISHOPFIXEDPAWNS -2
#define BISHOPMOBILITYMG 10
#define BISHOPMOBILITYEG 12

#define QUEENINFLITRATIONBONUS 43
#define QUEENMOBILITY 19
#define QUEENROOKFILE 38
#define QUEENBISHOPDIAGONAL 53

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
        Score += ISOLATEDPAWN;
    }

    // Check for isolated pawns
    if (((leftFileMask | rightFileMask) & FriendPawns.getBits()) == 0) {
        Score += DOUBLEDPAWN;
    }
    
    //check if pawn is in the centre squares 
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
        Score += ROOKOPENFILE ;
    }else if((oppPawns & fileMask) == 0){
        Score += ROOKSEMIOPENFILE;
    }

    if(isWhite && sq.rank() == chess::Rank::RANK_7){
        Score += ROOKBACKRANK;
    }else if(!isWhite && sq.rank() == chess::Rank::RANK_2){
        Score += ROOKBACKRANK;
    }

    chess::Bitboard RookMoves = chess::attacks::rook(sq, occ);
    
    Score += RookMoves.count() * static_cast<int>(weight * ROOKMOBILITYMG + (1.0f - weight) * ROOKMOBILITYEG);

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
    }else if((oppPawns & BishopBitBoard & BForward).count() < 2){
        Score += BISHOPSEMIOPENFILE;
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
    Score += (NoOfPawns - NoOfFixedPawns) * BISHOPNONFIXEDPAWNS;
    
    //Fixed Pawns are harder to get rid of so we should make them twice as bad
    Score += NoOfFixedPawns * BISHOPFIXEDPAWNS;

    Score += (BishopBitBoard & ~EnemyPawnsSq).count() * static_cast<int>(weight * BISHOPMOBILITYMG + (1.0f - weight) * BISHOPMOBILITYEG);

    return Score;
}

int EvaluateQueen(const chess::Board& board, const chess::Square &sq, chess::Bitboard& occ, chess::Bitboard& EnemyPawns, chess::Square Ksq, bool isWhite) {
    static const std::array<uint64_t, 15> Diagonals = {0x0000000000000080, 0x0000000000008040, 0x0000000000804020, 0x0000000080402010, 0x0000008040201008, 0x0000804020100804, 0x0080402010080402, 0x8040201008040201, 0x4020100804020100, 0x2010080402010000, 0x1008040201000000, 0x0804020100000000, 0x0402010000000000, 0x0201000000000000, 0x0100000000000000};
    static const std::array<uint64_t, 15> AntiDiagonals = {0x0000000000000001, 0x0000000000000102, 0x0000000000010204, 0x0000000001020408, 0x0000000102040810, 0x0000010204081020,0x0001020408102040, 0x0102040810204080,0x0204081020408000,0x0408102040800000,0x0810204080000000,0x1020408000000000, 0x2040800000000000,0x4080000000000000, 0x8000000000000000};
    
    int Score = 0;
    
    Score += chess::attacks::queen(sq, occ).count() * QUEENMOBILITY;

    //Calculate the enemy pawn span
    if(isWhite){
        chess::Bitboard BRearSpan = chess::Bitboard(0ULL);

        for (int i=1; i<8; i++) {
            uint64_t fileMask = 0x0101010101010101ULL << i;
            BRearSpan |= (NorthFill(chess::Bitboard(fileMask) & EnemyPawns));
        }

        if((BRearSpan & chess::Bitboard(sq.index())) != 0){
            Score += QUEENINFLITRATIONBONUS; //Infiltration bonus
        }

    }else{
        chess::Bitboard WRearSpan = chess::Bitboard(0ULL);

        for (int i=0; i<8; i++) {
            uint64_t fileMask = 0x0101010101010101ULL << i;
            WRearSpan |= (SouthFill(chess::Bitboard(fileMask) & EnemyPawns));
        }

        if((WRearSpan & chess::Bitboard(sq.index())) != 0){
            Score += QUEENINFLITRATIONBONUS; //Infiltration bonus
        }
    }
    
    // //Check if the queen is coordinating with other pieces
    chess::Bitboard Bishops = board.pieces(chess::PieceType::BISHOP, isWhite ? chess::Color::WHITE : chess::Color::BLACK);
    chess::Bitboard Rooks = board.pieces(chess::PieceType::ROOK, isWhite ? chess::Color::WHITE : chess::Color::BLACK);

    //Get the queens file bitboard
    chess::Bitboard QFile(0x0101010101010101ULL << sq.file());

    //See if its on the same file as a rook and are coordinating
    Score += (QFile & Rooks).count() * QUEENROOKFILE;
    
    //See if its on the same diagonal as the bishops and are coordinating
    if((Bishops & chess::Bitboard(Diagonals[sq.antidiagonal_of()])) != 0){
        Score += QUEENBISHOPDIAGONAL;
    }

    if((Bishops & chess::Bitboard(AntiDiagonals[sq.diagonal_of()]))){
        Score += QUEENBISHOPDIAGONAL;
    }

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