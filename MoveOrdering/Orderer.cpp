#include "..\ChessLib\chess-library\include\chess.hpp"
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

chess::Movelist Lumina::OrderMoves(const chess::Board& board, const chess::Move& HashMove, const int Ply)
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

        int Attacker = MovingPiece.type();
        int Victim   = Target.type();

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

        // // Promotions are likely to be good
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

chess::Movelist Lumina::OrderCaptures(const chess::Board& board, const chess::Move& HashMove)
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

        int Attacker = MovingPiece.type();
        int Victim   = Target.type();

        int AttackerScore = PiecesValue(Attacker);
        int VictimScore   = PiecesValue(Victim);

        if(move == HashMove){
            Score += HASH_SCORE;
        }

        // MVV-LVA + SEE
        Score += SEE(board, move, 0) ? CAPTURE_SCORE + (VictimScore - AttackerScore) : (VictimScore - AttackerScore);
        
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

chess::Movelist Lumina::OrderFromIteration(const chess::Movelist& LegalMoves, const std::vector<int>& MoveScores){
    assert(LegalMoves.size() == MoveScores.size());

    // 1) Build a vector of (score, move) pairs
    std::vector<std::pair<int, chess::Move>> scoredMoves;
    scoredMoves.reserve(LegalMoves.size());
    
    for (size_t i = 0; i < LegalMoves.size(); ++i) {
        scoredMoves.emplace_back(MoveScores[i], LegalMoves[i]);
    }

    // 2) Sort descending by score (stable so equal scores keep input order)
    std::stable_sort(
        scoredMoves.begin(), scoredMoves.end(),
        [](auto &a, auto &b) {
            return a.first > b.first;
        });

    // 3) Extract the ordered moves
    chess::Movelist Ordered;
    for (auto &p : scoredMoves) {
        Ordered.add(p.second);
    }

    return Ordered;
}