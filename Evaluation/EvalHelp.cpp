#include "..\ChessLib\chess.hpp"
#include "..\PrecomputedValues\Precomputed.h"
#include "..\Helper\HelperFunctions.h"

#include "EvalHelp.h"
#include <iostream>
#include <cmath>
#include <map>

int EvaluateKing(const chess::Square &KSq, const chess::Bitboard& occ, const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    int file = KSq.file();
    int rank = KSq.rank();

    // Check if King on open file
    uint64_t fileMask = ComputeFileMask(file);

    // Create bitboards for the adjacent files
    uint64_t flankFileMask = PrecomputedFlankFileMasks(file);

    // Combine the masks
    uint64_t combinedMask = fileMask | flankFileMask;

    int Score = 0;
    
    // See if the king has a pawn shield
    Score += (FriendPawns & combinedMask).count() * TaperedEvaluation(weight, NOPAWNSHIELD_MG, NOPAWNSHIELD_EG);

    // Virtual Queen Score  
    Score += chess::attacks::queen(KSq, occ).count() * TaperedEvaluation(weight, VQUEENSCOREMG, VQUEENSCOREEG);

    return Score;
}

int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    int Score = 0;

    int rank = sq.rank();
    int file = sq.file();

    uint64_t PForward = PrecomputedForwardMasks(rank, isWhite);

    // Create a bitboard for the same file
    uint64_t fileMask = ComputeFileMask(file);

    uint64_t flankMask = PrecomputedFlankFileMasks(file);

    // Combine the masks
    uint64_t combinedMask = fileMask | flankMask;

    // Apply the forward mask to get the relevant bits in front of the pawn
    uint64_t PawnBits = PForward & combinedMask;

    //Check if there are any opposing pawns in the relevant bits (Passed Pawn)
    //Or they are infront of the king which can be used to accellerate an attack on the king (Pawn Storm Heuristic)
    if ((PawnBits & EnemyPawns) == 0) {
        if (isWhite) {
            Score += TaperedEvaluation(weight, PawnBonuses[7 - rank], PawnBonusesEG[7 - rank]);
        } else {
            Score += TaperedEvaluation(weight, PawnBonuses[rank], PawnBonusesEG[rank]);
        }
    }

    chess::Bitboard sameFilePawns(fileMask & FriendPawns);
    chess::Bitboard currentPawnPosition(1ULL << sq.index());

    // Check if there are any other pawns on the same file (excluding the current pawn)
    if ((sameFilePawns & ~currentPawnPosition) != 0) {
        Score += TaperedEvaluation(weight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);
    }

    // Check for isolated pawns
    if ((flankMask & FriendPawns) == 0) {
        Score += TaperedEvaluation(weight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);
    }

    // if((isWhite && rank != 2) || (!isWhite && rank != 7)){
    //     // Check for Phalanx Pawns
    //     uint64_t PawnRank = (0xFFULL << (rank * 8)) & flankMask;

    //     Score += (PawnRank & FriendPawns).count() * TaperedEvaluation(weight, PHALANXBONUS_MG, PHALANXBONUS_EG);
    // }

    return Score;
}

int EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite){
    //We want Knights to be on outposts in the middle so they can control as many squares as possible
    //and basically harrass the other side
    int file = sq.file();
    int rank = sq.rank();

    //Get the bits behind one rank of the knight and in front of it
    uint64_t KForward  = PrecomputeKnightForward(rank, isWhite);
    uint64_t KBackward = PrecomputeKnightBackward(rank, isWhite);

    // Create bitboards for the adjacent files
    uint64_t CombinedMask = PrecomputedFlankFileMasks(file);

    //Apply the forward mask to get the relevant bits in front and behind the knight which creates like an X Shape
    uint64_t KnightBits = KForward & CombinedMask;

    int Score = 0;

    // See if a knight is on a outpost
    if (((KnightBits & EnemyPawns) == 0) && ((KBackward & FriendPawns) != 0)) {
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

    uint64_t fileMask = ComputeFileMask(file);

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

int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite){
    constexpr uint64_t LIGHT_SQUARES = 0x55AA55AA55AA55AAULL;
    constexpr uint64_t DARK_SQUARES  = 0xAA55AA55AA55AA55ULL;

    int Score = 0;

    int rank = sq.rank();
    int idx  = sq.index();

    chess::Bitboard BishopBitBoard = chess::attacks::bishop(sq, occ);

    // Create a combined mask which has both friendly and opposition pawns
    chess::Bitboard CombinedPawnMask = FriendPawns | EnemyPawns;

    // Create a forwards mask to delete all behind moves
    chess::Bitboard ForwardMask = ComputeBForward(rank, isWhite);

    // Check if bishop controls a open diagonal
    if((EnemyPawns & BishopBitBoard & ForwardMask) == 0){
        Score += TaperedEvaluation(weight, BISHOPOPENFILE_MG, BISHOPOPENFILE_EG);
    }

    // Detect Bad Bishop
    bool isLight = ((idx & 1) ^ (idx >> 3 & 1)) == 0;
    uint64_t colorMask = isLight ? LIGHT_SQUARES : DARK_SQUARES;
    
    chess::Bitboard ForwardColoredPawns = FriendPawns & ForwardMask & colorMask;

    chess::Bitboard MovablePawns = isWhite
        ? ((ForwardColoredPawns << 8) & ~EnemyPawns)
        : ((ForwardColoredPawns >> 8) & ~EnemyPawns);

    int NoOfPawns      = ForwardColoredPawns.count();
    int NonFixedPawns  = MovablePawns.count();
    int NoOfFixedPawns = NoOfPawns - NonFixedPawns;

    // Fixed Pawns are harder to get rid of
    Score += NoOfFixedPawns * TaperedEvaluation(weight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);
    Score += (BishopBitBoard ^ EnemyPawnsSq).count() * TaperedEvaluation(weight, BISHOPMOBILITY_MG, BISHOPMOBILITY_EG);

    return Score;
}