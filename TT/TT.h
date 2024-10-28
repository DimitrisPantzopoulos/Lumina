#ifndef TT_H
#define TT_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "../Lumina.h"
#include <vector>

struct TTEntry {
    int value;                   // Evaluation score
    int depth;                   // Depth of the search when this position was evaluated
    int nodeType;                // Type of node (upperbound, exact, lowerbound) (1, 2, 3) respectively
    chess::Move bestMove;        // Best move found from this position

    TTEntry() 
        : value(0), depth(0), nodeType(1), bestMove(chess::Move::NO_MOVE) {}  // Default constructor

    TTEntry(int v, int d, int nt, chess::Move bm)
        : value(v), depth(d), nodeType(nt), bestMove(bm) {}
};

#endif