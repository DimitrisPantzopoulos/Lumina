#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Helper\HelperFunctions.h"
<<<<<<< Updated upstream
=======
#include "..\EvaluationFeatures\Features.h"
>>>>>>> Stashed changes

#include "EvalHelp.h"
#include "Eval.h"

<<<<<<< Updated upstream
<<<<<<< Updated upstream
#define ImmediateMateScore 999999

#define BISHOPPAIR_MG 154
#define BISHOPPAIR_EG 144

int Evaluation(const chess::Board& board, int Ply){
    chess::GameResult State = board.isGameOver().second;

    if(State != chess::GameResult::NONE){
        if(State == chess::GameResult::WIN)      {return  (ImmediateMateScore - Ply);}
        else if(State == chess::GameResult::LOSE){return -(ImmediateMateScore - Ply);}
        else if(State == chess::GameResult::DRAW){return 0;}
    }

    int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    //Get both pawn bitboards which is used in the Bishop Evaluation and the squares which the pawns control because that is used in 
    //Space and knight evaluation
=======
constexpr uint64_t BOTTOM_HALF = 0x00000000FFFFFFFFULL;
constexpr uint64_t TOP_HALF    = 0xFFFFFFFF00000000ULL;

int Evaluation(const chess::Board& board){
    int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    // Get Bitboards for evaluation
>>>>>>> Stashed changes
    chess::Bitboard WPawns = board.pieces(chess::PieceType::PAWN, chess::Color::WHITE);
    chess::Bitboard BPawns = board.pieces(chess::PieceType::PAWN, chess::Color::BLACK);

    chess::Bitboard WKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::WHITE);
    chess::Bitboard BKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::BLACK);
    
    chess::Bitboard WBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::WHITE);
    chess::Bitboard BBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::BLACK);

    chess::Bitboard WRooks = board.pieces(chess::PieceType::ROOK, chess::Color::WHITE);
    chess::Bitboard BRooks = board.pieces(chess::PieceType::ROOK, chess::Color::BLACK);
    
    chess::Bitboard WQueen = board.pieces(chess::PieceType::QUEEN, chess::Color::WHITE);
    chess::Bitboard BQueen = board.pieces(chess::PieceType::QUEEN, chess::Color::BLACK);

    chess::Bitboard WKing = board.pieces(chess::PieceType::KING, chess::Color::WHITE);
    chess::Bitboard BKing = board.pieces(chess::PieceType::KING, chess::Color::BLACK);

    chess::Bitboard WPawnsThreats = GetPawnControlledSquares(WPawns, chess::Color::WHITE);
    chess::Bitboard BPawnsThreats = GetPawnControlledSquares(BPawns, chess::Color::BLACK);

    //We get the bitboards for both sides to combine them
    chess::Bitboard WhiteBitboard = WPawns | WKnights | WBishops | WRooks | WQueen | WKing;
    chess::Bitboard BlackBitboard = BPawns | BKnights | BBishops | BRooks | BQueen | BKing;
=======
int Evaluation(const chess::Board& board)
{
    int Perspective = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    constexpr uint64_t NOT_HFILE = ~0x8080808080808080ULL;
    constexpr uint64_t NOT_AFILE = ~0x0101010101010101ULL;

    // Get Bitboards for evaluation
    const chess::Bitboard WPawns = board.pieces(chess::PieceType::PAWN, chess::Color::WHITE);
    const chess::Bitboard BPawns = board.pieces(chess::PieceType::PAWN, chess::Color::BLACK);

    const chess::Bitboard WKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::WHITE);
    const chess::Bitboard BKnights = board.pieces(chess::PieceType::KNIGHT, chess::Color::BLACK);
    
    const chess::Bitboard WBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::WHITE);
    const chess::Bitboard BBishops = board.pieces(chess::PieceType::BISHOP, chess::Color::BLACK);

    const chess::Bitboard WRooks = board.pieces(chess::PieceType::ROOK, chess::Color::WHITE);
    const chess::Bitboard BRooks = board.pieces(chess::PieceType::ROOK, chess::Color::BLACK);
    
    const chess::Bitboard WQueen = board.pieces(chess::PieceType::QUEEN, chess::Color::WHITE);
    const chess::Bitboard BQueen = board.pieces(chess::PieceType::QUEEN, chess::Color::BLACK);

    const chess::Bitboard WKing = board.pieces(chess::PieceType::KING, chess::Color::WHITE);
    const chess::Bitboard BKing = board.pieces(chess::PieceType::KING, chess::Color::BLACK);

    const chess::Bitboard WPawnsThreats = (WPawns & NOT_HFILE) << 9 | (WPawns & NOT_AFILE) << 7;
    const chess::Bitboard BPawnsThreats = (BPawns & NOT_AFILE) >> 9 | (BPawns & NOT_HFILE) >> 7;

    //We get the bitboards for both sides to combine them
    const chess::Bitboard WhiteBitboard = WPawns | WKnights | WBishops | WRooks | WQueen | WKing;
    const chess::Bitboard BlackBitboard = BPawns | BKnights | BBishops | BRooks | BQueen | BKing;
>>>>>>> Stashed changes

    const chess::Bitboard CombinedBitboard = WhiteBitboard | BlackBitboard;

<<<<<<< Updated upstream
    //Now we get the indexes for all the pieces on the board so we can just check them and not have to loop over the entire board
    //Which is probably twice as efficient because we at most have to check 32 squares and not the entire 64 squares on the board
    //Also this function gets more efficient as the game progresses because less pieces = less indexes to check instead of having 
    //to check a constant 64 squares
    uint64_t Indexes = CombinedBitboard.getBits();
=======
    // Now we get the indexes for all the pieces on the board so we can just check them and not have to loop over the entire board
    // Which is probably twice as efficient because we at most have to check 32 squares and not the entire 64 squares on the board
    // Also this function gets more efficient as the game progresses because less pieces = less indexes to check instead of having 
    // to check a constant 64 squares
    chess::Bitboard Indexes = board.occ();
>>>>>>> Stashed changes

<<<<<<< Updated upstream
    double WhiteScore = 0;
    double BlackScore = 0;
=======
    int WhiteScore = 0;
    int BlackScore = 0;
>>>>>>> Stashed changes

    // Calculate the weight for endgame influence
    // Get the Weight form the opposition's side to know when to get aggresive
<<<<<<< Updated upstream
    // TODO: WE CAN PRECOMPUTE THIS ASWELL
    float WEndgameWeight = static_cast<float>(WhiteBitboard.count()) / 32.0f;
    float BEndgameWeight = static_cast<float>(BlackBitboard.count()) / 32.0f;
=======
    int WhitePieceCount  = WhiteBitboard.count();
    int BlackPieceCount  = BlackBitboard.count();

<<<<<<< Updated upstream
    double WEndgameWeight = static_cast<double>(BlackPieceCount) / 32.0;
    double BEndgameWeight = static_cast<double>(WhitePieceCount) / 32.0;
>>>>>>> Stashed changes
=======
    float WEndgameWeight = static_cast<float>(WhitePieceCount) / 16.0f;
    float BEndgameWeight = static_cast<float>(BlackPieceCount) / 16.0f;
>>>>>>> Stashed changes

    // Structural Evaluations
    EvaluatePawns(WPawns, BPawns, WhiteScore, BlackScore, WEndgameWeight, BEndgameWeight);
    EvaluateKnights(WKnights, BKnights, WPawns, BPawns, WPawnsThreats, BPawnsThreats, WhiteScore, BlackScore, WEndgameWeight, BEndgameWeight);
    EvaluateBishops(WBishops, BBishops, WPawns, BPawns, WPawnsThreats, BPawnsThreats, WhiteScore, BlackScore, WEndgameWeight, BEndgameWeight);
    EvaluateRooks(WRooks, BRooks, WPawns, BPawns, WhiteScore, BlackScore, WEndgameWeight, BEndgameWeight);
<<<<<<< Updated upstream

<<<<<<< Updated upstream
    while (Indexes) {
        // Get the Index
        int Index = __builtin_ctzll(Indexes);

        chess::Square Sq = chess::Square(Index);

        int  PieceType = static_cast<int>(board.at(Sq).type());
        bool Color     = board.at(Sq).color() == chess::Color::WHITE;

        if(Color){
            WhiteScore += PiecesValueEval(PieceType, BEndgameWeight) + PST(PieceType, true, Index, BEndgameWeight);

            switch (PieceType){
                case 0: // PAWN
                    WhiteScore += EvaluatePawn(Sq, BPawns, WPawns, BEndgameWeight, true);
                    break;
                case 1: // KNIGHT
                    WhiteScore += EvaluateKnight(Sq, BPawns, WPawns, BPawnsSq, BEndgameWeight, true);
                    break;
                case 2: // BISHOP
                    WhiteScore += EvaluateBishop(Sq, CombinedBitboard, BPawns, WPawns, BPawnsSq, BEndgameWeight, true);
                    WhiteBishops++;
                    break;
                case 3: // ROOKS
                    WhiteScore += EvaluateRooks(Sq, BPawns, WPawns, CombinedBitboard, BEndgameWeight, true);
                    break;
                case 4:
                    WhiteScore += EvaluateQueen(Sq, board, BPawns, CombinedBitboard, chess::Color::BLACK, BEndgameWeight);
                    break;
            }

        }else{
            BlackScore += PiecesValueEval(PieceType, WEndgameWeight) + PST(PieceType, false, Index, WEndgameWeight);

            switch (PieceType){
                case 0: // PAWN
                    BlackScore += EvaluatePawn(Sq, WPawns, BPawns, WEndgameWeight, false);
                    break;
                case 1: // KNIGHT
                    BlackScore += EvaluateKnight(Sq, WPawns, BPawns, WPawnsSq, WEndgameWeight, false);
                    break;
                case 2: // BISHOP
                    BlackScore += EvaluateBishop(Sq, CombinedBitboard, WPawns, BPawns, WPawnsSq, WEndgameWeight, false);
                    BlackBishops++;
                    break;
                case 3: // ROOK 
                    BlackScore += EvaluateRooks(Sq, WPawns, BPawns, CombinedBitboard, WEndgameWeight, false);
                    break;
                case 4: // QUEEN
                    BlackScore += EvaluateQueen(Sq, board, WPawns, CombinedBitboard, chess::Color::WHITE, WEndgameWeight);
                    break;
            }
        }

        Indexes &= Indexes - 1;
    }

    WhiteScore += WhiteBishops > 1 ? TaperedEvaluation(BEndgameWeight, BISHOPPAIR_MG, BISHOPPAIR_EG) : 0;
    BlackScore += BlackBishops > 1 ? TaperedEvaluation(WEndgameWeight, BISHOPPAIR_MG, BISHOPPAIR_EG) : 0;

    WhiteScore += SafetyScore(WKsq, CombinedBitboard, WPawns, BEndgameWeight, true);
    BlackScore += SafetyScore(BKsq, CombinedBitboard, BPawns, WEndgameWeight, false);
=======
    while (Indexes != 0) {
        const int Index = Indexes.pop();
        const chess::Square Sq(Index);
        const chess::Piece piece = board.at(Sq);
        const int PieceType = piece.type();
        const bool Color = piece.color() == chess::Color::WHITE;
    
        const float EndgameWeight  = Color ? WEndgameWeight : BEndgameWeight;
        const int   PSTIndex       = Color ? Index          : 63 - Index;
        double&        Score          = Color ? WhiteScore     : BlackScore;
        
        switch (PieceType) {
            case 0:
                Score += EvaluatePawn(Sq, EndgameWeight, Color, PSTIndex);
                break;
        
            case 1: {
                const chess::Bitboard EnemyPawnThreats = Color ? BPawnsThreats : WPawnsThreats;
                Score += EvaluateKnight(Sq, EnemyPawnThreats, EndgameWeight, PSTIndex);
                break;
            }
        
            case 2: {
                const chess::Bitboard EnemyPawns = Color ? BPawns : WPawns;
                const uint64_t HalfTest = Color ? TOP_HALF : BOTTOM_HALF;
                Score += EvaluateBishop(Sq, CombinedBitboard, EnemyPawns, HalfTest, EndgameWeight, PSTIndex);
                break;
            }
        
            case 3:
                Score += EvaluateRook(Sq, CombinedBitboard, EndgameWeight, PSTIndex);
                break;
        
            case 4:
                Score += EvaluateQueen(Sq, CombinedBitboard, EndgameWeight, PSTIndex);
                break;
        
            case 5: {
                const chess::Bitboard FriendlyPawns = Color ? WPawns : BPawns;
                Score += EvaluateKing(Sq, FriendlyPawns, CombinedBitboard, PSTIndex, EndgameWeight, Color);
                break;
            }
        
            default:
                break;
        }        
    }
>>>>>>> Stashed changes

    return (WhiteScore - BlackScore) * Perspective;
=======

    while (Indexes != 0) {
        const int Index = Indexes.pop();
        const chess::Square Sq(Index);
        const chess::Piece piece = board.at(Sq);
        const int PieceType = piece.type();
        const bool Color = piece.color() == chess::Color::WHITE;
    
        const float EndgameWeight  = Color ? WEndgameWeight : BEndgameWeight;
        const int   PSTIndex       = Color ? Index          : 63 - Index;
        int&        Score          = Color ? WhiteScore     : BlackScore;

        switch (PieceType) {
            case 0: // PAWN
                Score += EvaluatePawn(Sq, EndgameWeight, Color, PSTIndex);
                break;
        
            case 1: { // KNIGHT
                const chess::Bitboard& EnemyPawnThreats = Color ? BPawnsThreats : WPawnsThreats;
                Score += EvaluateKnight(Sq, EnemyPawnThreats, EndgameWeight, PSTIndex, Color);
                break;
            }
        
            case 2:
                Score += EvaluateBishop(Sq, CombinedBitboard, EndgameWeight, PSTIndex, Color);
                break;
        
            case 3:
                Score += EvaluateRook(Sq, CombinedBitboard, EndgameWeight, PSTIndex, Color);
                break;
        
            case 4:
                Score += EvaluateQueen(Sq, EndgameWeight, PSTIndex, Color);
                break;
        
            case 5: {
                const chess::Bitboard& FriendlyPawns = Color ? WPawns : BPawns;
                Score += EvaluateKing(Sq, FriendlyPawns, CombinedBitboard, EndgameWeight, PSTIndex, Color);
                break;
            }
        
            default:
                break;
        }        
    }

    return (WhiteScore - BlackScore) * Perspective ;
>>>>>>> Stashed changes
}