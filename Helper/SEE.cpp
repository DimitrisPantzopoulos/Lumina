#include "..\ChessLib\chess-library\include\chess.hpp"
#include "..\Evaluation\EvalHelp.h"

//|--------------------------------------------------------------------------------------------------|
//  STATIC EXCHANGE EVALUATION WAS MADE BY RAFID-DEV FOR RICE, WHICH IS LISCENCED UNDER THE GNU GPL-3.0
//  https://github.com/rafid-dev/rice/blob/main/src/see.cpp#L1    
//|--------------------------------------------------------------------------------------------------|
bool SEE(const chess::Board& board, const chess::Move& move, const int Threshold) {
    static const std::array<chess::PieceType, 6> pts = {chess::PieceType::PAWN, chess::PieceType::KNIGHT, chess::PieceType::BISHOP, chess::PieceType::ROOK, chess::PieceType::QUEEN, chess::PieceType::KING};

    chess::Square Target       = move.to();
    chess::Square TargetOrigin = move.from();

    chess::PieceType TargetType = board.at(Target).type();

    int value = PiecesValue(TargetType) - Threshold;

    if(value < 0){
        return false;
    }

    chess::PieceType Attacker = board.at(TargetOrigin).type();

    value -= PiecesValue(Attacker);

    if(value >= 0){
        return true;
    }

    chess::Bitboard occ = (board.occ() ^ (1ULL << TargetOrigin.index()) | 1ULL << Target.index());
    chess::Bitboard Attackers = chess::attacks::attackers(board, chess::Color::WHITE, Target) | chess::attacks::attackers(board, chess::Color::BLACK, Target);

    chess::Bitboard Queens  = board.pieces(chess::PieceType::QUEEN);
    chess::Bitboard Bishops = board.pieces(chess::PieceType::BISHOP);
    chess::Bitboard Rooks   = board.pieces(chess::PieceType::ROOK);

    chess::Color EnemyColor = ~board.at(TargetOrigin).color();

    while(true){
        Attackers &= occ;

        chess::Bitboard NowAttacking = Attackers & board.us(EnemyColor);

        if(!NowAttacking){
            break;
        }

        chess::PieceType pt;
        for(int i=0; i<=5; i++){
            pt = pts[i];

            if(NowAttacking & (board.pieces(pt))){
                break;
            }
        }

        EnemyColor = ~EnemyColor;

        if((value = -value - 1 - PiecesValue(pt)) >= 0){
            if(pt == chess::PieceType::KING && (Attackers & board.us(EnemyColor))){
                EnemyColor = ~EnemyColor;    
            }

            break;
        }

        occ ^= (1ULL << (NowAttacking & board.pieces(pt)).lsb());

        if(pt == chess::PieceType::PAWN || pt == chess::PieceType::BISHOP || pt == chess::PieceType::QUEEN){
            NowAttacking |= chess::attacks::bishop(Target, occ) & Bishops;
        }

        if(pt == chess::PieceType::ROOK || pt == chess::PieceType::QUEEN){
            NowAttacking |= chess::attacks::rook(Target, occ) & Rooks;
        }
    }

    return EnemyColor != board.at(TargetOrigin).color();
}