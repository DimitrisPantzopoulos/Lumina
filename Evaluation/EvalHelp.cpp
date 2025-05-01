#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"

#include "EvalHelp.h"

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

    uint64_t WhitePawnsMask = WhitePawns.getBits();
    uint64_t BlackPawnsMask = BlackPawns.getBits();

    // Get Diagonals
    // White
    uint64_t WDiagonalsNE = (WhitePawnsMask & NOT_HFILE) << 9;
    uint64_t WDiagonalsNW = (WhitePawnsMask & NOT_AFILE) << 7;

    // Black
    uint64_t BDiagonalsNE = (BlackPawnsMask & NOT_AFILE) >> 9;
    uint64_t BDiagonalsNW = (BlackPawnsMask & NOT_HFILE) >> 7;

    uint64_t WhitePawnsPassedPawnMask = NorthFill(WDiagonalsNE | WhitePawnsMask | WDiagonalsNW);
    uint64_t BlackPawnsPassedPawnMask = SouthFill(BDiagonalsNE | BlackPawnsMask | BDiagonalsNW);

    // Find how many Passed Pawns each side has
    int WhitePassedPawns = __builtin_popcountll(~BlackPawnsPassedPawnMask & WhitePawnsMask);
    WhiteScore += WhitePassedPawns * TaperedEvaluation(Wweight, PASSEDPAWN_MG, PASSEDPAWN_EG);

    int BlackPassedPawns = __builtin_popcountll(~WhitePawnsPassedPawnMask & BlackPawnsMask);
    BlackScore += BlackPassedPawns * TaperedEvaluation(Bweight, PASSEDPAWN_MG, PASSEDPAWN_EG);

    // Find out how many Doubled Pawns each side has
    int WhiteDoubledPawns = __builtin_popcountll(SouthFill(WhitePawnsMask >> 8) & WhitePawnsMask);
    WhiteScore += WhiteDoubledPawns * TaperedEvaluation(Wweight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);

    int BlackDoubledPawns = __builtin_popcountll(NorthFill(BlackPawnsMask << 8) & BlackPawnsMask);
    BlackScore += BlackDoubledPawns * TaperedEvaluation(Bweight, DOUBLEDPAWN_MG, DOUBLEDPAWN_EG);

    // Find How many Isolated Pawns there are on each file for each side
    uint64_t WAdjacent = WDiagonalsNE | WDiagonalsNW;
    uint64_t BAdjacent = BDiagonalsNE | BDiagonalsNW;

    uint64_t WhiteAdjacentFileMasks = NorthFill(WAdjacent) | SouthFill(WAdjacent);
    uint64_t BlackAdjacentFileMasks = NorthFill(BAdjacent) | SouthFill(BAdjacent);
    
    int WhiteIsoPawns = __builtin_popcountll(~WhiteAdjacentFileMasks & WhitePawnsMask);
    WhiteScore += WhiteIsoPawns * TaperedEvaluation(Wweight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);

    int BlackIsoPawns = __builtin_popcountll(~BlackAdjacentFileMasks & BlackPawnsMask);
    BlackScore += BlackIsoPawns * TaperedEvaluation(Bweight, ISOLATEDPAWN_MG, ISOLATEDPAWN_EG);
}

void EvaluateKnights(
    const chess::Bitboard& WhiteKnights,            const chess::Bitboard& BlackKnights,
    const chess::Bitboard& WhitePawns,              const chess::Bitboard& BlackPawns,
    const chess::Bitboard& WhitePawnsAttackSquares, const chess::Bitboard& BlackPawnsAttackSquares,
    int& WhiteScore, int& BlackScore, float Wweight, float Bweight
)
{
    constexpr uint64_t NOT_HFILE = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE = ~0x0101010101010101ULL;

    constexpr uint64_t BOTTOM_HALF = 0x00000000FFFFFFFFULL;
    constexpr uint64_t TOP_HALF    = 0xFFFFFFFF00000000ULL;

    // Get Masks
    uint64_t WhiteKnightsMask = WhiteKnights.getBits();
    uint64_t BlackKnightsMask = BlackKnights.getBits();

    uint64_t WhitePawnSupportSquares = WhitePawnsAttackSquares.getBits();
    uint64_t BlackPawnSupportSquares = BlackPawnsAttackSquares.getBits();
    
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
    

    int BlackOutposts = __builtin_popcountll(BlackKnightsMask & BlackPawnSupportSquares & BOTTOM_HALF & ~WhiteAdjacent);
    BlackScore += BlackOutposts * TaperedEvaluation(Bweight, KNIGHTOUTPOST_MG, KNIGHTOUTPOST_EG);
}

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

    uint64_t FixedPawns    = ((WhitePawnsMask << 8) & BlackPawnsMask) | ((BlackPawnsMask >> 8) & WhitePawnsMask);
    uint64_t NonFixedPawns = CombinedPawnMask & ~FixedPawns;

    int LightFixedPawns    = __builtin_popcountll(FixedPawns & LIGHT_SQUARES);
    int LightNonFixedPawns = __builtin_popcountll(NonFixedPawns & LIGHT_SQUARES);

    int DarkFixedPawns    = __builtin_popcountll(FixedPawns & DARK_SQUARES);
    int DarkNonFixedPawns = __builtin_popcountll(NonFixedPawns & DARK_SQUARES);

    // ────────── WHITE ──────────
    int whiteLightFixed = WhiteLightBishops * LightFixedPawns;
    int whiteDarkFixed  = WhiteDarkBishops  * DarkFixedPawns;

    WhiteScore += (whiteLightFixed + whiteDarkFixed) * TaperedEvaluation(Wweight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);

    // ────────── BLACK ──────────
    int blackLightFixed   = BlackLightBishops * LightFixedPawns;
    int blackDarkFixed    = BlackDarkBishops  * DarkFixedPawns;

    BlackScore += (blackLightFixed + blackDarkFixed) * TaperedEvaluation(Bweight, BISHOPFIXEDPAWNS_MG, BISHOPFIXEDPAWNS_EG);
}
