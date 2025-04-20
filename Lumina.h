#ifndef LUMINA_H
#define LUMINA_H

#include "ChessLib\chess-library\include\chess.hpp"
#include "Evaluation/Eval.h"
#include "TT/TT.h"

#include <unordered_map>
#include <atomic>
#include <thread>
#include <string>
#include <vector>

using namespace chess;
using namespace std;

class Lumina {
    private:
        std::atomic<bool> CanSearch {true};
        
        KMT KillerMoveTable   = KMT();
        TT TranspositionTable = TT();
        
    public:
        Movelist OrderMoves   (const chess::Board& board, const chess::Move& HashMove, const int Ply);
        Movelist OrderCaptures(const Board& board, const Move& HashMove);

        Move Think(Board& board, int Milliseconds);
        int  Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions);
        int  QSearch(Board& board, int alpha, int beta, int Ply);

        void ClearTT();
        void ClearKMT();
};

#endif
