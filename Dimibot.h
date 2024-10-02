#ifndef DIMIBOT_H
#define DIMIBOT_H

#include "ChessLib\chess-library-master\include\chess.hpp"
#include "Evaluation/Eval.h"
#include "TT/TT.h"
#include <unordered_map>
#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

using namespace chess;
using namespace std;

class Dimibot {
    private:
        Move BestMoveFound = Move::NO_MOVE;
        unordered_map<uint64_t, TTEntry> TT;

    public:
        Move Think(Board& board, int Milliseconds);
        int Search(chess::Board& board, int Ply ,int PlyRemaining, int alpha, int beta, int Extensions);
        int QSearch(Board& board, int alpha, int beta, int Ply);

        void storeTTEntry(const uint64_t key, int value, int depth, int nodeType, chess::Move bestMove);
        bool retrieveTTEntry(const uint64_t key, TTEntry &entry, int depth);
        void ClearTT();
};

#endif
