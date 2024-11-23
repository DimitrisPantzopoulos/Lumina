#ifndef LUMINA_H
#define LUMINA_H

#include "ChessLib\chess-library-master\include\chess.hpp"
#include "Evaluation/Eval.h"
#include "TT/TT.h"

#include <unordered_map>
#include <atomic>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib>

using namespace chess;
using namespace std;

class Lumina {
    private:
        std::atomic<bool> CanSearch {true};
        
        KMT KillerMoveTable;
        TT TT;
        
    public:
        Movelist OrderMoves   (chess::Board& board, chess::Move& HashMove, const int Ply);
        Movelist OrderCaptures(Board& board, Move& HashMove);

        Move Think(Board& board, int Milliseconds);
        int  Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions);
        int  QSearch(Board& board, int alpha, int beta, int Ply);

        void ClearTT();
        void ClearKMT();
};

#endif
