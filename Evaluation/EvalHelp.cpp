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

#define PAWN_VALUE_MG 286.704f
#define PAWN_VALUE_EG 319.704f
#define KNIGHT_VALUE_MG 975.878f
#define KNIGHT_VALUE_EG 867.878f
#define BISHOP_VALUE_MG 952.684f
#define BISHOP_VALUE_EG 981.684f
#define ROOK_VALUE_MG 1458.65f
#define ROOK_VALUE_EG 1716.65f
#define QUEEN_VALUE_MG 3412.55f
#define QUEEN_VALUE_EG 3151.55f
#define NOPAWNSHIELD_MG 7.17343f
#define NOPAWNSHIELD_EG 15.1735f
#define VQUEENSCOREMG -18.9678f
#define VQUEENSCOREEG -5.96784f
#define ISOLATEDPAWN_MG -19.4982f
#define ISOLATEDPAWN_EG -15.4982f
#define DOUBLEDPAWN_MG -40.2878f
#define DOUBLEDPAWN_EG -29.2878f
#define CENTREPAWN_MG -4.87463f
#define CENTREPAWN_EG -8.87463f
#define PHALANXBONUS_MG 2.91307f
#define PHALANXBONUS_EG 6.91307f
#define KNIGHTOUTPOST_MG 82.4478f
#define KNIGHTOUTPOST_EG 71.4478f
#define KNIGHTMOBILITY_MG 35.3411f
#define KNIGHTMOBILITY_EG 29.3411f
#define ROOKOPENFILE_MG 43.072f
#define ROOKOPENFILE_EG 64.072f
#define ROOKBACKRANK_MG 77.4299f
#define ROOKBACKRANK_EG 57.4299f
#define ROOKMOBILITYMG 16.4595f
#define ROOKMOBILITYEG 17.4595f
#define BISHOPOPENFILE_MG 13.6482f
#define BISHOPOPENFILE_EG 19.6482f
#define BISHOPFIXEDPAWNS_MG -5.95287f
#define BISHOPFIXEDPAWNS_EG 5.04713f
#define BISHOPMOBILITYMG 24.0471f
#define BISHOPMOBILITYEG 26.0471f
#define QUEENMOBILITY_MG -10.3852f
#define QUEENMOBILITY_EG -13.3852f
#define QUEENMIDDLESQUAREPRESSURE_MG 4.04914f
#define QUEENMIDDLESQUAREPRESSURE_EG 1.04914f
#define QUEENDISTANCE_MG -46.5486f
#define QUEENDISTANCE_EG -41.5486f
#define BISHOPPAIR_MG 154.475f
#define BISHOPPAIR_EG 144.475f

float PiecesValueEval(const chess::PieceType& PieceType, float weight) {
    if (PieceType == chess::PieceType::PAWN)          {return TaperedEvaluation(weight, PAWN_VALUE_MG, PAWN_VALUE_EG);} 
    else if (PieceType == chess::PieceType::KNIGHT)   {return TaperedEvaluation(weight, KNIGHT_VALUE_MG, KNIGHT_VALUE_EG);}
    else if (PieceType == chess::PieceType::BISHOP)   {return TaperedEvaluation(weight, BISHOP_VALUE_MG, BISHOP_VALUE_EG);} 
    else if (PieceType == chess::PieceType::ROOK)     {return TaperedEvaluation(weight, ROOK_VALUE_MG, ROOK_VALUE_EG);}
    else if (PieceType == chess::PieceType::QUEEN)    {return TaperedEvaluation(weight, QUEEN_VALUE_MG, QUEEN_VALUE_EG);}

    return 0.0f;
}

float SafetyScore(const chess::Square &KSq, const chess::Bitboard& occ ,const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    int file = KSq.file();
    int rank = KSq.rank();

    uint64_t KForward;

    if (isWhite) {
        KForward = 0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8);
    } else {
        KForward = 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8);
    }

    // Check if King on open file
    uint64_t fileMask = 0x0101010101010101ULL << file;

    // Create bitboards for the adjacent files
    uint64_t leftFileMask = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
    uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

    // Combine the masks
    uint64_t combinedMask = (fileMask | leftFileMask | rightFileMask) & KForward;

    float SafetyScore = 0.0f;
    
    // See if the king has a pawn shield
    SafetyScore += (FriendPawns & combinedMask).count() * TaperedEvaluation(weight, NOPAWNSHIELD_MG, NOPAWNSHIELD_EG);

    // Virtual Queen Score  
    SafetyScore += chess::attacks::queen(KSq, occ).count() * TaperedEvaluation(weight, VQUEENSCOREMG, VQUEENSCOREEG);

    return SafetyScore;
}

float EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    constexpr static std::array<int, 7> PawnBonuses = {0, 94, 202, 128, 60, 2, 8};
    constexpr static std::array<int, 7> PawnBonusesEG = {0, 85, 187, 111, 54, -1, 7};
    static const uint64_t Msquares = 0x1818000000;

    float Score = 0.0f;
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
            
            Score += TaperedEvaluation(weight, PawnBonuses[7 - rank], PawnBonusesEG[7 - rank]);
        } else {
            Score += TaperedEvaluation(weight, PawnBonuses[rank], PawnBonusesEG[rank]);
        }
    }

    chess::Bitboard sameFilePawns(fileMask & FriendPawns.getBits());
    chess::Bitboard currentPawnPosition(1ULL << sq.index());

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

    // Check for Phalanx Pawns
    chess::Bitboard PawnRank(0xFFULL << (rank * 8));
    PawnRank &= leftFileMask | rightFileMask;

    if((isWhite && rank != 2) || (!isWhite && rank != 7)){
        Score += (PawnRank & FriendPawns).count() * TaperedEvaluation(weight, PHALANXBONUS_MG, PHALANXBONUS_EG);
    }

    return Score;
}

float EvaluateKnight(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& SCBEP, float weight, bool isWhite){
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

    float Score = 0.0f;

    // See if a knight is on a outpost
    if (((KnightBits & EnemyPawns.getBits()) == 0) && ((KBackward & FriendPawns.getBits()) != 0)) {
        Score += TaperedEvaluation(weight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
    }

    // Check Knight mobility but disregard squares that pawns are on
    chess::Bitboard KnightMoves = chess::attacks::knight(sq);

    Score += (KnightMoves & ~SCBEP).count() * TaperedEvaluation(weight, KNIGHTMOBILITY_MG, KNIGHTMOBILITY_EG);

    return Score;
}

float EvaluateRooks(const chess::Square &sq, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& occ, float weight, bool isWhite){
    float Score = 0.0f;

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
    
    Score += RookMoves.count() * TaperedEvaluation(weight, ROOKMOBILITYMG, ROOKMOBILITYEG);

    return Score;
}

float EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite){
    static const chess::Bitboard LIGHT_SQUARES= chess::Bitboard(0x55AA55AA55AA55AAULL);
    static const chess::Bitboard DARK_SQUARES = chess::Bitboard(0xAA55AA55AA55AA55ULL);

    chess::Bitboard BishopBitBoard = chess::attacks::bishop(sq, occ);
    
    int rank = sq.rank();

    // Create a combined mask which has both friendly and opposition pawns
    chess::Bitboard CombinedMask = FriendPawns | EnemyPawns;

    // Create a forwards mask to delete all behind moves
    chess::Bitboard BForward;

    if (isWhite) {
        BForward = 0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8);
    } else {
        BForward = 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8);
    }

    // Combine Backwards and BishopBitboard to have only the forwards moves
    float Score = 0.0f;

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
    if((chess::Bitboard(1ULL << sq.index()) & LIGHT_SQUARES) != 0){
        // If its a light squared bishop

        // Find how many total pawns there are blocking the bishop
        chess::Bitboard WhiteSquaredPawns = (LIGHT_SQUARES & FriendPawns) & BForward;
        NoOfPawns = (WhiteSquaredPawns).count();

        // Find out how many Fixed pawns Pawns that dont move are in the position
        if(isWhite){
            NoOfFixedPawns = ((WhiteSquaredPawns << 8) & EnemyPawns).count();
        }else{
            NoOfFixedPawns = ((WhiteSquaredPawns >> 8) & EnemyPawns).count();
        }

    }else{
        // Find how many total pawns there are blocking the bishop
        chess::Bitboard BlackSquaredPawns = (DARK_SQUARES & FriendPawns) & BForward;
        NoOfPawns = (BlackSquaredPawns).count();

        // Find out how many Fixed pawns Pawns that dont move are in the position
        if(isWhite){
            NoOfFixedPawns = ((BlackSquaredPawns << 8) & EnemyPawns).count();
        }else{
            NoOfFixedPawns = ((BlackSquaredPawns >> 8) & EnemyPawns).count();
        }
    }

    // Fixed Pawns are harder to get rid of so we should make them twice as bad
    Score += NoOfFixedPawns * TaperedEvaluation(weight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);

    Score += (BishopBitBoard & ~EnemyPawnsSq).count() * TaperedEvaluation(weight, BISHOPMOBILITYMG, BISHOPMOBILITYEG);

    return Score;
}

float EvaluateQueen(const chess::Board& board, const chess::Bitboard& EnemyPawns, const chess::Bitboard occ, const chess::Square &sq, const chess::Color EnemyColor, float weight){
    static const chess::Bitboard Msquares = chess::Bitboard(0x1818000000ULL);

    float Score = 0.0f;

    // Count mobility
    chess::Bitboard QueenMobility = chess::attacks::queen(sq, occ);
    //Score += QueenMobility.count() * TaperedEvaluation(weight, QUEENMOBILITY_MG, QUEENMOBILITY_EG);

    // // Pressure on Middle Squares
    Score += (QueenMobility & Msquares).count() * TaperedEvaluation(weight, QUEENMIDDLESQUAREPRESSURE_MG, QUEENMIDDLESQUAREPRESSURE_EG);

    // Calculate distance to king to see how big of a threat it is to king safety
    //Score += 1.0f / (chess::Square::distance(sq, board.kingSq(EnemyColor))) * TaperedEvaluation(weight, QUEENDISTANCE_MG, QUEENDISTANCE_EG);

    return Score;
}