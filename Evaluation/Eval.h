#ifndef EVAL_H
#define EVAL_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include <map>

using namespace chess;
using namespace std;

int Evaluation(const Board& board, int Ply);

#endif

