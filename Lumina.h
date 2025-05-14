#ifndef LUMINA_H
#define LUMINA_H

#include "ChessLib\chess.hpp"
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
        
        KMT KillerMoveTable    = KMT();
        TT  TranspositionTable = TT();
        HT  HistoryTable       = HT();
        CT  CounterTable       = CT();
        
    public:
        chess::Movelist OrderMoves   (const chess::Board& board, const chess::Move& HashMove, const chess::Move& LastMove ,const int Ply);
        chess::Movelist OrderCaptures(const chess::Board& board, const Move& HashMove);
        chess::Movelist OrderFromIteration(const chess::Movelist& LegalMoves, const std::vector<int>& MoveScores);
        
        void Think(chess::Board& board, int Milliseconds);
        int  Search(chess::Board& board, int Ply, int PlyRemaining, int alpha, int beta, int Extensions, const chess::Move& LastMove);
        int  QSearch(chess::Board& board, int alpha, int beta, int Ply);

        void ClearTT();
        void ClearKMT();
        void ClearHT();
        void ClearCT();
};

#endif
