#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"
#include "EvalHelp.h"
<<<<<<< Updated upstream

#include <iostream>
#include <cmath>
#include <map>

<<<<<<< Updated upstream
constexpr int PAWN_VALUE_MG = 286;
constexpr int PAWN_VALUE_EG = 319;

constexpr int KNIGHT_VALUE_MG = 975;
constexpr int KNIGHT_VALUE_EG = 867;

constexpr int BISHOP_VALUE_MG = 952;
constexpr int BISHOP_VALUE_EG = 981;

constexpr int ROOK_VALUE_MG = 1458;
constexpr int ROOK_VALUE_EG = 1716;

constexpr int QUEEN_VALUE_MG = 3412;
constexpr int QUEEN_VALUE_EG = 3151;

constexpr int NOPAWNSHIELD_MG = 7;
constexpr int NOPAWNSHIELD_EG = 15;
=======
// Structural Evaluation functions all O(1) parrallelised, bit-manipulation functions and are crazy fast on average 6x faster than traditional implementations
// Not to mention how mnay bugs I squashed when making these its crazy
void EvaluatePawns(
    const chess::Bitboard& WhitePawns, const chess::Bitboard& BlackPawns, 
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight)
{
    constexpr uint64_t Msquares = 0x1818000000;
    constexpr uint64_t NOT_HFILE = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE = ~0x0101010101010101ULL;
>>>>>>> Stashed changes
=======

// Structural Evaluation functions all O(1) parrallelised, bit-manipulation functions and are crazy fast on average 6x faster than traditional implementations
// Not to mention how many bugs I squashed when making these its crazy
void EvaluatePawns(
    const chess::Bitboard& WhitePawns, const chess::Bitboard& BlackPawns, 
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
)
{
    constexpr uint64_t MIDDLE_SQUARES =  0x0000001818000000ULL;
    constexpr uint64_t NOT_HFILE      = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE      = ~0x0101010101010101ULL;
>>>>>>> Stashed changes

    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

<<<<<<< Updated upstream
    uint64_t WDiagonalsNE = (WhitePawnsMask & NOT_HFILE) << 9;
    uint64_t WDiagonalsNW = (WhitePawnsMask & NOT_AFILE) << 7;

=======
    // Get Diagonals
    // White
    uint64_t WDiagonalsNE = (WhitePawnsMask & NOT_HFILE) << 9;
    uint64_t WDiagonalsNW = (WhitePawnsMask & NOT_AFILE) << 7;

    // Black
>>>>>>> Stashed changes
    uint64_t BDiagonalsNE = (BlackPawnsMask & NOT_AFILE) >> 9;
    uint64_t BDiagonalsNW = (BlackPawnsMask & NOT_HFILE) >> 7;

    uint64_t WhitePawnsPassedPawnMask = NorthFill(WDiagonalsNE | WhitePawnsMask | WDiagonalsNW);
    uint64_t BlackPawnsPassedPawnMask = SouthFill(BDiagonalsNE | BlackPawnsMask | BDiagonalsNW);

    // Find how many Passed Pawns each side has
<<<<<<< Updated upstream
    WhiteScore += __builtin_popcountll(~BlackPawnsPassedPawnMask & WhitePawnsMask) * TaperedEvaluation(Wweight, PASSEDPAWN_MG, PASSEDPAWN_EG);
    BlackScore += __builtin_popcountll(~WhitePawnsPassedPawnMask & BlackPawnsMask) * TaperedEvaluation(Bweight, PASSEDPAWN_MG, PASSEDPAWN_EG);

    // Find out how many Doubled Pawns each side has
    WhiteScore += __builtin_popcountll(SouthFill(WhitePawnsMask >> 8) & WhitePawnsMask) * TaperedEvaluation(Wweight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);
    BlackScore += __builtin_popcountll(NorthFill(BlackPawnsMask << 8) & BlackPawnsMask) * TaperedEvaluation(Bweight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);

    // Find How many Isolated Pawns there are on each file for each side
    uint64_t WAdjacent = WDiagonalsNE | WDiagonalsNW;
    uint64_t BAdjacent = BDiagonalsNE | BDiagonalsNW;

<<<<<<< Updated upstream
constexpr int ROOKOPENFILE_MG = 43;
constexpr int ROOKOPENFILE_EG = 64;
=======
    int WhitePassedPawns = __builtin_popcountll(~BlackPawnsPassedPawnMask & WhitePawnsMask);
    WhiteScore += WhitePassedPawns * TaperedEvaluation(Wweight, PASSEDPAWN_MG, PASSEDPAWN_EG);

    int BlackPassedPawns = __builtin_popcountll(~WhitePawnsPassedPawnMask & BlackPawnsMask);
    BlackScore += BlackPassedPawns * TaperedEvaluation(Bweight, PASSEDPAWN_MG, PASSEDPAWN_EG);

    // Find out how many Doubled Pawns each side has
    int WhiteDoubledPawns = __builtin_popcountll(SouthFill(WhitePawnsMask >> 8) & WhitePawnsMask);
    WhiteScore += WhiteDoubledPawns * TaperedEvaluation(Wweight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);

    int BlackDoubledPawns = __builtin_popcountll(NorthFill(BlackPawnsMask << 8) & BlackPawnsMask);
    BlackScore += BlackDoubledPawns * TaperedEvaluation(Bweight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);
>>>>>>> Stashed changes

    // Find How many Isolated Pawns there are on each file for each side
    uint64_t WAdjacent = WDiagonalsNE | WDiagonalsNW;
    uint64_t BAdjacent = BDiagonalsNE | BDiagonalsNW;

<<<<<<< Updated upstream
constexpr int ROOKMOBILITY_MG = 16;
constexpr int ROOKMOBILITY_EG = 17;

constexpr int BISHOPOPENFILE_MG = 13;
constexpr int BISHOPOPENFILE_EG = 19;

constexpr int BISHOPFIXEDPAWNS_MG = -5;
constexpr int BISHOPFIXEDPAWNS_EG = 5;

constexpr int BISHOPMOBILITY_MG = 24;
constexpr int BISHOPMOBILITY_EG = 26;

constexpr int QUEENMOBILITY_MG = -10;
constexpr int QUEENMOBILITY_EG = -13;

constexpr int QUEENMIDDLESQUAREPRESSURE_MG = 4;
constexpr int QUEENMIDDLESQUAREPRESSURE_EG = 1;

constexpr int QUEENDISTANCE_MG = -46;
constexpr int QUEENDISTANCE_EG = -41;

int PiecesValueEval(const int& PieceType, float weight) {
    switch (static_cast<int>(PieceType)) {
        case 0: // PAWN
            return TaperedEvaluation(weight, PAWN_VALUE_MG, PAWN_VALUE_EG);
        case 1: // KNIGHT
            return TaperedEvaluation(weight, KNIGHT_VALUE_MG, KNIGHT_VALUE_EG);
        case 2: // BISHOP
            return TaperedEvaluation(weight, BISHOP_VALUE_MG, BISHOP_VALUE_EG);
        case 3: // ROOK
            return TaperedEvaluation(weight, ROOK_VALUE_MG, ROOK_VALUE_EG);
        case 4: // QUEEN
            return TaperedEvaluation(weight, QUEEN_VALUE_MG, QUEEN_VALUE_EG);
        default:
            return  0;
    }
}

int SafetyScore(const chess::Square &KSq, const chess::Bitboard& occ ,const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    int file = KSq.file();
    int rank = KSq.rank();

    // Check if King on open file
    uint64_t fileMask = 0x0101010101010101ULL << file;

    // Create bitboards for the adjacent files
    uint64_t leftFileMask  = (file > 0) ? 0x0101010101010101ULL << (file - 1) : 0;
    uint64_t rightFileMask = (file < 7) ? 0x0101010101010101ULL << (file + 1) : 0;

    // Combine the masks
    uint64_t combinedMask = (fileMask | leftFileMask | rightFileMask);

    int SafetyScore = 0;
=======
    uint64_t WhiteAdjacentFileMasks = NorthFill(WAdjacent) | SouthFill(WAdjacent);
    uint64_t BlackAdjacentFileMasks = NorthFill(BAdjacent) | SouthFill(BAdjacent);
>>>>>>> Stashed changes
    
    WhiteScore += __builtin_popcountll(~WhiteAdjacentFileMasks & WhitePawnsMask) * TaperedEvaluation(Wweight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);
    BlackScore += __builtin_popcountll(~BlackAdjacentFileMasks & BlackPawnsMask) * TaperedEvaluation(Bweight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);

    // Find out how many pawns are in the center
    WhiteScore += __builtin_popcountll(WhitePawnsMask & Msquares) * TaperedEvaluation(Wweight, CENTREPAWN_MG, CENTREPAWN_EG);
    BlackScore += __builtin_popcountll(BlackPawnsMask & Msquares) * TaperedEvaluation(Bweight, CENTREPAWN_MG, CENTREPAWN_EG);
}

<<<<<<< Updated upstream
int EvaluatePawn(const chess::Square &sq, const chess::Bitboard &EnemyPawns, const chess::Bitboard &FriendPawns, float weight, bool isWhite) {
    constexpr static std::array<int, 7> PawnBonuses =   {0, 94, 202, 128, 60, 2, 8};
    constexpr static std::array<int, 7> PawnBonusesEG = {0, 85, 187, 111, 54, -1, 7};
=======
=======
    uint64_t WhiteAdjacentFileMasks = NorthFill(WAdjacent) | SouthFill(WAdjacent);
    uint64_t BlackAdjacentFileMasks = NorthFill(BAdjacent) | SouthFill(BAdjacent);
    
    int WhiteIsoPawns = __builtin_popcountll(~WhiteAdjacentFileMasks & WhitePawnsMask);
    WhiteScore += WhiteIsoPawns * TaperedEvaluation(Wweight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);

    int BlackIsoPawns = __builtin_popcountll(~BlackAdjacentFileMasks & BlackPawnsMask);
    BlackScore += BlackIsoPawns * TaperedEvaluation(Bweight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);
}

>>>>>>> Stashed changes
void EvaluateKnights(
    const chess::Bitboard& WhiteKnights,            const chess::Bitboard& BlackKnights,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares, const chess::Bitboard& BlackPawnsAttackSquares,
<<<<<<< Updated upstream
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight)
{
    constexpr uint64_t NOT_HFILE = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE = ~0x0101010101010101ULL;
>>>>>>> Stashed changes
=======
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
)
{
    constexpr uint64_t NOT_HFILE = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE = ~0x0101010101010101ULL;
>>>>>>> Stashed changes

    constexpr uint64_t BOTTOM_HALF = 0x00000000FFFFFFFFULL;
    constexpr uint64_t TOP_HALF    = 0xFFFFFFFF00000000ULL;

<<<<<<< Updated upstream
<<<<<<< Updated upstream
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
=======
=======
>>>>>>> Stashed changes
    // Get Masks
    uint64_t WhiteKnightsMask = WhiteKnights.getBits();
    uint64_t BlackKnightsMask = BlackKnights.getBits();

    uint64_t WhitePawnSupportSquares = WhitePawnsAttackSquares.getBits();
    uint64_t BlackPawnSupportSquares = BlackPawnsAttackSquares.getBits();
<<<<<<< Updated upstream
>>>>>>> Stashed changes
    
    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

<<<<<<< Updated upstream
    // Check for Phalanx Pawns
    chess::Bitboard PawnRank(0xFFULL << (rank * 8));
    PawnRank &= leftFileMask | rightFileMask;

    if((isWhite && rank != 2) || (!isWhite && rank != 7)){
        Score += (PawnRank & FriendPawns).count() * TaperedEvaluation(weight, PHALANXBONUS_MG, PHALANXBONUS_EG);
    }
=======
    // Direct forward fills
    uint64_t WhitePawnsNorthFill = NorthFill(WhitePawnsMask);
    uint64_t BlackPawnsSouthFill = SouthFill(BlackPawnsMask);

    // WHITE
    uint64_t WhitePawnsNEFill = (WhitePawnsNorthFill & NOT_HFILE) << 9; // NE = up+right
    uint64_t WhitePawnsNWFill = (WhitePawnsNorthFill & NOT_AFILE) << 7; // NW = up+left
>>>>>>> Stashed changes

    // BLACK
    uint64_t BlackPawnsNEFill = (BlackPawnsSouthFill & NOT_AFILE) >> 7; // SE = down+right
    uint64_t BlackPawnsNWFill = (BlackPawnsSouthFill & NOT_HFILE) >> 9; // SW = down+left

    // Passed pawn masks
    uint64_t WhiteAdjacent = WhitePawnsNEFill | WhitePawnsNWFill;
    uint64_t BlackAdjacent = BlackPawnsNEFill | BlackPawnsNWFill;

    // Calculate Outposts
    WhiteScore += __builtin_popcountll((WhiteKnightsMask & WhitePawnSupportSquares & TOP_HALF) & ~BlackAdjacent) * TaperedEvaluation(Wweight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
    BlackScore += __builtin_popcountll((BlackKnightsMask & BlackPawnSupportSquares & BOTTOM_HALF) & ~WhiteAdjacent) * TaperedEvaluation(Bweight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
}

void EvaluateRooks(
    const chess::Bitboard& WhiteRooks,              const chess::Bitboard& BlackRooks,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight)
{
    constexpr uint64_t RANK_2 = 0x000000000000FF00ULL;
    constexpr uint64_t RANK_7 = 0x00FF000000000000ULL;

<<<<<<< Updated upstream
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
=======
    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

    uint64_t WhiteRooksMask = WhiteRooks.getBits();
    uint64_t BlackRooksMask = BlackRooks.getBits();
>>>>>>> Stashed changes

    // Find which rooks are on a open file
    uint64_t CombinedPawnsMask = WhitePawnsMask | BlackPawnsMask;

    // Open File and Semi-Open File
    uint64_t WhitePawnSouthFill = SouthFill(WhitePawnsMask);
    uint64_t BlackPawnSouthFill = SouthFill(BlackPawnsMask);

<<<<<<< Updated upstream
    // See if a knight is on a outpost
    if (((KnightBits & EnemyPawns.getBits()) == 0) && ((KBackward & FriendPawns.getBits()) != 0)) {
        Score += TaperedEvaluation(weight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
    }
=======
    uint64_t WhitePawnNorthFill = NorthFill(WhitePawnsMask);
    uint64_t BlackPawnNorthFill = NorthFill(BlackPawnsMask);
>>>>>>> Stashed changes

    uint64_t WhitePawnColumnFills = WhitePawnNorthFill | WhitePawnSouthFill;
    uint64_t BlackPawnColumnFills = BlackPawnNorthFill | BlackPawnSouthFill;

    // Open File Heuristic
    WhiteScore += __builtin_popcountll((WhiteRooksMask & ~WhitePawnColumnFills) & ~BlackPawnColumnFills) * TaperedEvaluation(Wweight, ROOKOPENFILE_MG, ROOKOPENFILE_EG);
    BlackScore += __builtin_popcountll((BlackRooksMask & ~BlackPawnColumnFills) & ~WhitePawnColumnFills) * TaperedEvaluation(Bweight, ROOKOPENFILE_MG, ROOKOPENFILE_EG);

    // 2nd and 7th Rank Heuristic
    WhiteScore += __builtin_popcountll(WhiteRooksMask & RANK_7) * TaperedEvaluation(Wweight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);
    BlackScore += __builtin_popcountll(BlackRooksMask & RANK_2) * TaperedEvaluation(Bweight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);
}

<<<<<<< Updated upstream
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
=======
    
    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

    // Direct forward fills
    uint64_t WhitePawnsNorthFill = NorthFill(WhitePawnsMask);
    uint64_t BlackPawnsSouthFill = SouthFill(BlackPawnsMask);

    // WHITE
    uint64_t WhitePawnsNEFill = (WhitePawnsNorthFill & NOT_HFILE) << 9; // NE = up+right
    uint64_t WhitePawnsNWFill = (WhitePawnsNorthFill & NOT_AFILE) << 7; // NW = up+left

    // BLACK
    uint64_t BlackPawnsNEFill = (BlackPawnsSouthFill & NOT_AFILE) >> 9; // SE = down+right
    uint64_t BlackPawnsNWFill = (BlackPawnsSouthFill & NOT_HFILE) >> 7; // SW = down+left

    // Passed pawn masks
    uint64_t WhiteAdjacent = WhitePawnsNEFill | WhitePawnsNWFill;
    uint64_t BlackAdjacent = BlackPawnsNEFill | BlackPawnsNWFill;

    // Calculate Outposts
    int WhiteOutposts = __builtin_popcountll(WhiteKnightsMask & WhitePawnSupportSquares & TOP_HALF & ~BlackAdjacent);
    WhiteScore += WhiteOutposts * TaperedEvaluation(Wweight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
>>>>>>> Stashed changes
    

    int BlackOutposts = __builtin_popcountll(BlackKnightsMask & BlackPawnSupportSquares & BOTTOM_HALF & ~WhiteAdjacent);
    BlackScore += BlackOutposts * TaperedEvaluation(Bweight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
}

<<<<<<< Updated upstream
int EvaluateBishop(const chess::Square &sq, const chess::Bitboard occ, const chess::Bitboard& EnemyPawns, const chess::Bitboard& FriendPawns, const chess::Bitboard& EnemyPawnsSq, float weight, bool isWhite){
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

    // Fixed Pawns are harder to get rid of
    Score += NoOfFixedPawns * TaperedEvaluation(weight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);

    Score += (BishopBitBoard & ~EnemyPawnsSq).count() * TaperedEvaluation(weight, BISHOPMOBILITY_MG, BISHOPMOBILITY_EG);

    return Score;
}

int EvaluateQueen(const chess::Square &sq, const chess::Board& board, const chess::Bitboard& EnemyPawns, const chess::Bitboard occ, const chess::Color EnemyColor, float weight){
    static const chess::Bitboard Msquares = chess::Bitboard(0x1818000000ULL);

    int Score = 0;

    // Count mobility
    chess::Bitboard QueenMobility = chess::attacks::queen(sq, occ);
    //Score += QueenMobility.count() * TaperedEvaluation(weight, QUEENMOBILITY_MG, QUEENMOBILITY_EG);

    // // Pressure on Middle Squares
    Score += (QueenMobility & Msquares).count() * TaperedEvaluation(weight, QUEENMIDDLESQUAREPRESSURE_MG, QUEENMIDDLESQUAREPRESSURE_EG);

    // Calculate distance to king to see how big of a threat it is to king safety
    //Score += 1.0f / (chess::Square::distance(sq, board.kingSq(EnemyColor))) * TaperedEvaluation(weight, QUEENDISTANCE_MG, QUEENDISTANCE_EG);
=======
void EvaluateBishops(
    const chess::Bitboard& WhiteBishops,            const chess::Bitboard& BlackBishops,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares, const chess::Bitboard& BlackPawnsAttackSquares,
    double& WhiteScore, double& BlackScore, const double Wweight, const double Bweight)
{
    constexpr uint64_t LIGHT_SQUARES = 0x55AA55AA55AA55AAULL;
    constexpr uint64_t DARK_SQUARES  = 0xAA55AA55AA55AA55ULL;

    uint64_t WhiteBishopsMask = WhiteBishops.getBits();
    uint64_t BlackBishopsMask = BlackBishops.getBits();
    
    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

    // Detect Bad Bishops
    int WhiteLightBishops = __builtin_popcountll(WhiteBishopsMask & LIGHT_SQUARES);
    int WhiteDarkBishops  = __builtin_popcountll(WhiteBishopsMask & DARK_SQUARES);

    int BlackLightBishops = __builtin_popcountll(BlackBishopsMask & LIGHT_SQUARES);
    int BlackDarkBishops  = __builtin_popcountll(BlackBishopsMask & DARK_SQUARES);

    // Calculate Scores
    uint64_t CombinedPawnMask = WhitePawnsMask | BlackPawnsMask;
>>>>>>> Stashed changes

=======
void EvaluateRooks(
    const chess::Bitboard& WhiteRooks,              const chess::Bitboard& BlackRooks,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
)
{
    constexpr uint64_t RANK_2 = 0x000000000000FF00ULL;
    constexpr uint64_t RANK_7 = 0x00FF000000000000ULL;

    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

    uint64_t WhiteRooksMask = WhiteRooks.getBits();
    uint64_t BlackRooksMask = BlackRooks.getBits();

    // Find which rooks are on a open file
    uint64_t CombinedPawnsMask = WhitePawnsMask | BlackPawnsMask;

    // Open File and Semi-Open File
    uint64_t WhitePawnSouthFill = SouthFill(WhitePawnsMask);
    uint64_t BlackPawnSouthFill = SouthFill(BlackPawnsMask);
    uint64_t WhitePawnNorthFill = NorthFill(WhitePawnsMask);
    uint64_t BlackPawnNorthFill = NorthFill(BlackPawnsMask);

    uint64_t WhitePawnColumnFills = WhitePawnNorthFill | WhitePawnSouthFill;
    uint64_t BlackPawnColumnFills = BlackPawnNorthFill | BlackPawnSouthFill;

    int WhiteOpenFiles = __builtin_popcountll((WhiteRooksMask & ~WhitePawnColumnFills) & ~BlackPawnColumnFills);
    WhiteScore += WhiteOpenFiles * TaperedEvaluation(Wweight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);

    int BlackOpenFiles = __builtin_popcountll((BlackRooksMask & ~BlackPawnColumnFills) & ~WhitePawnColumnFills);
    BlackScore += BlackOpenFiles * TaperedEvaluation(Bweight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);

    // 2nd and 7th Rank Heuristic
    int WhiteRooksOn7th = __builtin_popcountll(WhiteRooksMask & RANK_7);
    int BlackRooksOn2nd = __builtin_popcountll(BlackRooksMask & RANK_2);

    WhiteScore += WhiteRooksOn7th * TaperedEvaluation(Wweight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);
    BlackScore += BlackRooksOn2nd * TaperedEvaluation(Bweight, ROOKBACKRANK_MG, ROOKBACKRANK_EG);
}

void EvaluateBishops(
    const chess::Bitboard& WhiteBishops,            const chess::Bitboard& BlackBishops,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares, const chess::Bitboard& BlackPawnsAttackSquares,
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
)
{
    constexpr uint64_t LIGHT_SQUARES = 0x55AA55AA55AA55AAULL;
    constexpr uint64_t DARK_SQUARES  = 0xAA55AA55AA55AA55ULL;

    uint64_t WhiteBishopsMask = WhiteBishops.getBits();
    uint64_t BlackBishopsMask = BlackBishops.getBits();
    
    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

    // Detect Bad Bishops
    int WhiteLightBishops = __builtin_popcountll(WhiteBishopsMask & LIGHT_SQUARES);
    int WhiteDarkBishops  = __builtin_popcountll(WhiteBishopsMask & DARK_SQUARES);

    int BlackLightBishops = __builtin_popcountll(BlackBishopsMask & LIGHT_SQUARES);
    int BlackDarkBishops  = __builtin_popcountll(BlackBishopsMask & DARK_SQUARES);

    // Calculate Scores
    uint64_t CombinedPawnMask = WhitePawnsMask | BlackPawnsMask;

>>>>>>> Stashed changes
    uint64_t FixedPawns    = ((WhitePawnsMask << 8) & BlackPawnsMask) | ((BlackPawnsMask >> 8) & WhitePawnsMask);
    uint64_t NonFixedPawns = CombinedPawnMask & ~FixedPawns;

    int LightFixedPawns    = __builtin_popcountll(FixedPawns & LIGHT_SQUARES);
    int LightNonFixedPawns = __builtin_popcountll(NonFixedPawns & LIGHT_SQUARES);

    int DarkFixedPawns    = __builtin_popcountll(FixedPawns & DARK_SQUARES);
    int DarkNonFixedPawns = __builtin_popcountll(NonFixedPawns & DARK_SQUARES);

<<<<<<< Updated upstream
    int WhiteFixedTapered = TaperedEvaluation(Wweight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);
    int BlackFixedTapered = TaperedEvaluation(Bweight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);

    int WhiteNonFixedTapered = TaperedEvaluation(Wweight, NONFIXEDPAWN_MG, NONFIXEDPAWN_EG);
    int BlackNonFixedTapered = TaperedEvaluation(Bweight, NONFIXEDPAWN_MG, NONFIXEDPAWN_EG);

    WhiteScore += WhiteLightBishops * (LightFixedPawns * WhiteFixedTapered + LightNonFixedPawns * WhiteNonFixedTapered);
    WhiteScore += WhiteDarkBishops  * (DarkFixedPawns  * WhiteFixedTapered + DarkNonFixedPawns  * WhiteNonFixedTapered);
    WhiteScore += ((WhiteLightBishops + WhiteDarkBishops) >= 2) * TaperedEvaluation(Wweight, TWOBISHOPS_MG, TWOBISHOPS_EG);

    BlackScore += BlackLightBishops * (LightFixedPawns * BlackFixedTapered + LightNonFixedPawns * BlackNonFixedTapered);
    BlackScore += BlackDarkBishops  * (DarkFixedPawns  * BlackFixedTapered + DarkNonFixedPawns  * BlackNonFixedTapered);
    BlackScore += ((BlackLightBishops + BlackDarkBishops) >= 2) * TaperedEvaluation(Bweight, TWOBISHOPS_MG, TWOBISHOPS_EG);
}
=======
    // ────────── WHITE ──────────
    int whiteLightFixed = WhiteLightBishops * LightFixedPawns;
    int whiteDarkFixed  = WhiteDarkBishops  * DarkFixedPawns;

    WhiteScore += (whiteLightFixed + whiteDarkFixed) * TaperedEvaluation(Wweight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);

    // ────────── BLACK ──────────
    int blackLightFixed   = BlackLightBishops * LightFixedPawns;
    int blackDarkFixed    = BlackDarkBishops  * DarkFixedPawns;

    BlackScore += (blackLightFixed + blackDarkFixed) * TaperedEvaluation(Bweight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);
}
>>>>>>> Stashed changes
