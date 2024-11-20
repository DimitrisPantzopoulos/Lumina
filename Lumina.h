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
#include <ctime> 

using namespace chess;
using namespace std;

class Lumina {
    private:
        unordered_map<uint64_t, TTEntry> TT;
        KMT KillerMoveTable;

        std::atomic<bool> CanSearch {true};

    public:
        Movelist OrderMoves   (chess::Board& board, chess::Move& HashMove, const int Ply);
        Movelist OrderCaptures(Board& board, Move& HashMove);

        Move Think(Board& board, int Milliseconds);
        int Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions);
        int QSearch(Board& board, int alpha, int beta, int Ply);

        void storeTTEntry(const uint64_t key, int value, int depth, int nodeType, chess::Move bestMove);
        bool retrieveTTEntry(const uint64_t key, TTEntry &entry, int depth);
        void ClearTT();
        void ClearKMT();

        Lumina(){
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
        }
};

#endif
