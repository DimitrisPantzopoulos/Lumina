#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"
#include "EvalHelp.h"

#include <iostream>
#include <cmath>
#include <map>

int SafetyScore(const chess::Square &KSq, const chess::Bitboard& occ ,const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    int file = KSq.file();
    int rank = KSq.rank();

    // Check if King on open file
    uint64_t fileMask = 0x0101010101010101ULL << file;

    // Create bitboards for the adjacent files
    uint64_t leftFileMask  = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
    uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

    // Combine the masks
    uint64_t CombinedMask = (fileMask | leftFileMask | rightFileMask);

    int SafetyScore = 0;
    
    // See if the king has a pawn shield
    SafetyScore += (FriendPawns & CombinedMask).count() * TaperedEvaluation(weight, NOPAWNSHIELD_MG, NOPAWNSHIELD_EG);

    // Virtual Queen Score
    SafetyScore += chess::attacks::queen(KSq, occ).count() * TaperedEvaluation(weight, VQUEENSCOREMG, VQUEENSCOREEG);

    return SafetyScore;
}

int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    constexpr static std::array<int, 7> PawnBonuses =   {0, 94, 202, 128, 60, 2, 8};
    constexpr static std::array<int, 7> PawnBonusesEG = {0, 85, 187, 111, 54, -1, 7};

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
    uint64_t fileMask(0x0101010101010101ULL << file);

    // Create bitboards for the adjacent files
    uint64_t leftFileMask ((file > 0) ? 0x0101010101010101ULL << (file - 1) : 0);
    uint64_t rightFileMask((file < 7) ? 0x0101010101010101ULL << (file + 1) : 0);

    // Combine the masks
    uint64_t CombinedMask = fileMask | leftFileMask | rightFileMask;

    // Apply the forward mask to get the relevant bits in front of the pawn
    uint64_t PawnBits = PForward & CombinedMask;

    // Check if there are any opposing pawns in the relevant bits (Passed Pawn)
    // Or they are infront of the king which can be used to accellerate an attack on the king (Pawn Storm Heuristic)
    if ((PawnBits & EnemyPawns) == 0) {
        if (isWhite) {
            Score += TaperedEvaluation(weight, PawnBonuses[7 - rank], PawnBonusesEG[7 - rank]);
        } else {
            Score += TaperedEvaluation(weight, PawnBonuses[rank], PawnBonusesEG[rank]);
        }
    }

    uint64_t sameFilePawns(fileMask & FriendPawns.getBits());
    uint64_t currentPawnPosition(1ULL << sq.index());

    // Check if there are any other pawns on the same file (excluding the current pawn)
    if ((sameFilePawns & ~currentPawnPosition) != 0) {
        Score += TaperedEvaluation(weight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);
    }

    // Check for isolated pawns
    if (((leftFileMask | rightFileMask) & FriendPawns) == 0) {
        Score += TaperedEvaluation(weight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);
    }
    
    // Check if pawn is in the centre squares 
    if((currentPawnPosition & Msquares) != 0){
        Score += TaperedEvaluation(weight, CENTREPAWN_MG, CENTREPAWN_EG);
    }

    if((isWhite && rank != 2) || (!isWhite && rank != 7)){
        // Check for Phalanx Pawns
        chess::Bitboard PawnRank(0xFFULL << (rank * 8));
        PawnRank &= leftFileMask | rightFileMask;

        Score += (PawnRank & FriendPawns).count() * TaperedEvaluation(weight, PHALANXBONUS_MG, PHALANXBONUS_EG);
    }

    return Score;
}

int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite){
    //We want Knights to be on outposts in the middle so they can control as many squares as possible
    //and basically harrass the other side
    int file = sq.file();
    int rank = sq.rank();

    //Get the bits behind one rank of the knight and in front of it
    uint64_t KForward;
    uint64_t KBackward;

    if (isWhite) {
        KForward  = (rank > 0) ? 0xFFFFFFFFFFFFFFFFULL << ((rank+1) * 8) : 0;
        KBackward = (sq.index() >= 9 ? 0x5ULL << (sq.index() - 9) : 0) & ~0x8181818181818181;
    }else {
        KForward  = (rank < 7) ? 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8) : 0;
        KBackward = (sq.index() <= 56 ? 0x5ULL << (sq.index() + 7) : 0) & ~0x8181818181818181;
    }

    // Create bitboards for the adjacent files
    uint64_t leftFileMask = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
    uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

    uint64_t CombinedMask = leftFileMask | rightFileMask;

    //Apply the forward mask to get the relevant bits in front and behind the knight which creates like an X Shape
    uint64_t KnightBits = KForward & CombinedMask;

    int Score = 0;

    // See if a knight is on a outpost
    if (((KnightBits & EnemyPawns.getBits()) == 0) && ((KBackward & FriendPawns.getBits()) != 0)) {
        Score += TaperedEvaluation(weight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
    }

    // Check Knight mobility but disregard squares that pawns are on
    chess::Bitboard KnightMoves = chess::attacks::knight(sq);

    Score += (KnightMoves & ~SCBEP).count() * TaperedEvaluation(weight, KNIGHTMOBILITY_MG, KNIGHTMOBILITY_EG);

    return Score;
}

int EvaluateRooks(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ, float weight, bool isWhite){
    int Score = 0;

    //Get the file the rook is on and make it into a bitboard
    int file = sq.file();

    uint64_t fileMask = 0x0101010101010101ULL << file;

    //Check if the rook is on a open file
    if(((EnemyPawns | FriendPawns) & fileMask) == 0){
        Score += TaperedEvaluation(weight, ROOKOPENFILE_MG, ROOKOPENFILE_EG);
    }

    if(isWhite && sq.rank() == chess::Rank::RANK_7){
        Score += TaperedEvaluation(weight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);
    }else if(!isWhite && sq.rank() == chess::Rank::RANK_2){
        Score += TaperedEvaluation(weight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);
    }

    chess::Bitboard RookMoves = chess::attacks::rook(sq, occ);
    
    Score += RookMoves.count() * TaperedEvaluation(weight, ROOKMOBILITY_MG, ROOKMOBILITY_EG);

    return Score;
}

int EvaluateBishop(const chess::Square &sq, const chess::Bitboard& occ, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite){
    static constexpr uint64_t LIGHT_SQUARES = 0x55AA55AA55AA55AAULL;
    static constexpr uint64_t DARK_SQUARES  = 0xAA55AA55AA55AA55ULL;

    int rank = sq.rank();

    chess::Bitboard BishopBitBoard = chess::attacks::bishop(sq, occ);

    // Create a combined mask which has both friendly and opposition pawns
    chess::Bitboard CombinedMask = FriendPawns | EnemyPawns;

    // Create a forwards mask to delete all behind moves
    uint64_t BForward;

    if (isWhite) {
        BForward = 0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8);
    } else {
        BForward = 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8);
    }

    // Combine Backwards and BishopBitboard to have only the forwards moves
    int Score = 0;

    // Check if bishop controls a open diagonal
    // The reason for < 2 is because the bishop can only control max 2 open diagonals if i didnt do this
    // it could control a open diagonal and not be rewarded for it
    if((CombinedMask & BishopBitBoard).count() < 2){
        Score += TaperedEvaluation(weight, BISHOPOPENFILE_MG, BISHOPOPENFILE_EG);
    }

    // Detect Bad Bishop
    int NoOfFixedPawns;
    int NoOfPawns;

    // Is bishop light or dark squared?
    if(((1ULL << sq.index()) & LIGHT_SQUARES) != 0){
        // If its a light squared bishop

        // Find how many total pawns there are blocking the bishop
        chess::Bitboard WhiteSquaredPawns = (LIGHT_SQUARES & FriendPawns) & BForward;
        NoOfPawns = WhiteSquaredPawns.count();

        // Find out how many Fixed pawns Pawns that dont move are in the position
        if(isWhite){
            NoOfFixedPawns = ((WhiteSquaredPawns << 8) & EnemyPawns).count();
        }else{
            NoOfFixedPawns = ((WhiteSquaredPawns >> 8) & EnemyPawns).count();
        }

    }else{
        // Find how many total pawns there are blocking the bishop
        chess::Bitboard BlackSquaredPawns = (DARK_SQUARES & FriendPawns) & BForward;

        NoOfPawns = BlackSquaredPawns.count();

        // Find out how many Fixed pawns Pawns that dont move are in the position
        if(isWhite){
            NoOfFixedPawns = ((BlackSquaredPawns << 8) & EnemyPawns).count();
        }else{
            NoOfFixedPawns = ((BlackSquaredPawns >> 8) & EnemyPawns).count();
        }
    }

    // Fixed Pawns are harder to get rid of
    Score += NoOfFixedPawns * TaperedEvaluation(weight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);

    Score += (BishopBitBoard & ~EnemyPawnsSq).count() * TaperedEvaluation(weight, BISHOPMOBILITY_MG, BISHOPMOBILITY_EG);

    return Score;
}

int EvaluateQueen(const chess::Square &sq, const chess::Board& board, const chess::Bitboard& EnemyPawns, const chess::Bitboard& occ, const chess::Color EnemyColor, float weight){
    static const chess::Bitboard Msquares = chess::Bitboard(0x1818000000ULL);

    int Score = 0;

    // Count mobility
    chess::Bitboard QueenMobility = chess::attacks::queen(sq, occ);
    //Score += QueenMobility.count() * TaperedEvaluation(weight, QUEENMOBILITY_MG, QUEENMOBILITY_EG);

    // // Pressure on Middle Squares
    Score += (QueenMobility & Msquares).count() * TaperedEvaluation(weight, QUEENMIDDLESQUAREPRESSURE_MG, QUEENMIDDLESQUAREPRESSURE_EG);

    // Calculate distance to king to see how big of a threat it is to king safety
    //Score += 1.0f / (chess::Square::distance(sq, board.kingSq(EnemyColor))) * TaperedEvaluation(weight, QUEENDISTANCE_MG, QUEENDISTANCE_EG);

    return Score;
}