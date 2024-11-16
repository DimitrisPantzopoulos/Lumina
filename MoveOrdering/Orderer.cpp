#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Helper\SEE.h"
#include "..\Lumina.h"
#include "..\Helper\HelperFunctions.h"

#include <algorithm>
#include <vector>

//Values and small bits of the code based off Small-Brains Implementation - https://github.com/Disservin/Smallbrain/blob/main/src/movepick.h#L153 by Disservin
enum MoveTypes : int {
    HASH_SCORE          =  10000000,
    CAPTURE_SCORE       =  7000000,
    FIRST_KILLER_SCORE  =  6000000,
    SECOND_KILLER_SCORE =  5000000,
    NEGATIVE_SCORE      = -10000000,
};

struct ScoredMove {
    chess::Move move;
    int score;
};

bool compareMoves(const ScoredMove &a, const ScoredMove &b) {
    return a.score > b.score;
}

chess::Movelist Lumina::OrderMoves(chess::Board& board, chess::Move& HashMove, const int Ply)
{
    chess::Movelist KillerMoves = KillerMoveTable.getKillerMoves(Ply);

    chess::Color OppColor = board.sideToMove() == chess::Color::WHITE ? chess::Color::BLACK : chess::Color::WHITE;

    chess::Movelist Moves;
    chess::movegen::legalmoves(Moves, board);

    std::vector<ScoredMove> ScoredMoves;

    //Extract the sorted moves into a Movelist
    chess::Movelist SortedMoves;

    for (const auto &move : Moves){
        int Score = 0;

        chess::Square FromSq = move.from();
        chess::Square ToSq = move.to();

        chess::Piece MovingPiece = board.at(FromSq);
        chess::Piece Target      = board.at(ToSq);

        chess::PieceType Attacker = MovingPiece.type();
        chess::PieceType Victim   = Target.type();

        int AttackerScore = PiecesValue(Attacker);
        int VictimScore   = PiecesValue(Victim);

        if(move == HashMove){
            Score += HASH_SCORE;
        }else if(move == KillerMoves[0]){
            Score += FIRST_KILLER_SCORE;
        }else if(move == KillerMoves[1]){
            Score += SECOND_KILLER_SCORE;
        }

        // Prioritise captures
        if(Target != chess::Piece::NONE)
        {
            // MVV-LVA + SEE
            Score += SEE(board, move, 0) ? CAPTURE_SCORE + (VictimScore - AttackerScore) : (VictimScore - AttackerScore);
        }

        // Promotions are likely to be good
        else if(move.typeOf() == chess::Move::PROMOTION){
            chess::PieceType PromotionType = move.promotionType();
            Score += PiecesValue(PromotionType);
        }

        // Discourage the pieces from going to squares that are being attacked
        else if(board.isAttacked(ToSq, OppColor)){
            Score -= AttackerScore;
        }

        ScoredMoves.push_back({move, Score});
    }

    // Sort moves by score in descending order
    std::sort(ScoredMoves.begin(), ScoredMoves.end(), compareMoves);

    for (const auto &scoredMove : ScoredMoves) {
        SortedMoves.add(scoredMove.move);
    }

    return SortedMoves;
}

chess::Movelist Lumina::OrderCaptures(chess::Board& board, chess::Move& HashMove)
{
    chess::Movelist Moves;
    chess::movegen::legalmoves<chess::movegen::MoveGenType::CAPTURE>(Moves, board);

    std::vector<ScoredMove> ScoredMoves;

    // Extract the sorted moves into a Movelist
    chess::Movelist SortedMoves;

    for (const auto &move : Moves){
        int Score = 0;

        chess::Square FromSq = move.from();
        chess::Square ToSq = move.to();

        chess::Piece MovingPiece = board.at(FromSq);
        chess::Piece Target = board.at(ToSq);

        chess::PieceType Attacker = MovingPiece.type();
        chess::PieceType Victim   = Target.type();

        int AttackerScore = PiecesValue(Attacker);
        int VictimScore   = PiecesValue(Victim);

        if(move == HashMove){
            Score += HASH_SCORE;
        }

        // MVV-LVA + SEE
        Score += CAPTURE_SCORE + (VictimScore - AttackerScore);
        
        if (Score >= 0){
            ScoredMoves.push_back({move, Score});
        }
    }

    // Sort moves by score in descending order
    std::sort(ScoredMoves.begin(), ScoredMoves.end(), compareMoves);

    for (const auto &scoredMove : ScoredMoves) {
        SortedMoves.add(scoredMove.move);
    }

    return SortedMoves;
}