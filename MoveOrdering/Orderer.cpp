#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Evaluation\Eval.h"
#include "..\Helper\SEE.h"
#include <algorithm>
#include <vector>

struct ScoredMove {
    chess::Move move;
    int score;
};

bool compareMoves(const ScoredMove &a, const ScoredMove &b) {
    return a.score > b.score;
}

bool find(chess::Movelist& moves, chess::Move move){
    for(int i=0; i<moves.size(); i++){
        if(moves[i] == move){return true;}
    }

    return false;
}   

chess::Movelist OrderMoves(chess::Board& board, chess::Move& BestMove)
{
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
        chess::Piece Target = board.at(ToSq);

        chess::PieceType MovingPieceType = MovingPiece.type();
        chess::PieceType TargetType = Target.type();

        int MovingPieceScore = PiecesValue(MovingPieceType);
        int TargetScore = PiecesValue(TargetType);

        if(move == BestMove){
            SortedMoves.add(move);
            continue;
        }
        
        //Prioritise captures
        if(Target != chess::Piece::NONE)
        {
            Score += SEE(board, move);
        }

        //Promotions are likely to be good
        else if(move.typeOf() == chess::Move::PROMOTION){
            chess::PieceType PromotionType = move.promotionType();
            Score += PiecesValue(PromotionType);
        }
        //Discourage the pieces from going to squares that are being attacked
        else if(board.isAttacked(ToSq, OppColor)){
            Score -= MovingPieceScore;
        }

        ScoredMoves.push_back({move, Score});
    }

    //Sort moves by score in descending order
    std::sort(ScoredMoves.begin(), ScoredMoves.end(), compareMoves);

    for (const auto &scoredMove : ScoredMoves) {
        SortedMoves.add(scoredMove.move);
    }

    return SortedMoves;
}

chess::Movelist OrderCaptures(chess::Board& board)
{
    chess::Movelist Moves;
    chess::movegen::legalmoves<chess::movegen::MoveGenType::CAPTURE>(Moves, board);

    std::vector<ScoredMove> ScoredMoves;

    for (const auto &move : Moves){

        int Score = SEE(board, move);
        
        if(Score <= 0){
            continue;
        }
        
        ScoredMoves.push_back({move, Score});
    }

    //Sort moves by score in descending order
    std::sort(ScoredMoves.begin(), ScoredMoves.end(), compareMoves);

    //Extract the sorted moves into a Movelist
    chess::Movelist SortedMoves;

    for (const auto &scoredMove : ScoredMoves) {
        SortedMoves.add(scoredMove.move);
    }

    return SortedMoves;
}