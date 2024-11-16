#ifndef EVAL_H
#define EVAL_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\PST\PST.h"
#include <map>

using namespace chess;
using namespace std;

float Evaluation(const Board& board, int Ply);

#endif

