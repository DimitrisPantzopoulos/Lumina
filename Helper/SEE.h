#ifndef SEE_H
#define SEE_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Evaluation\Eval.h"
#include "HelperFunctions.h"

#include <vector>

#define Infinity 9999999

int SEE(chess::Board& board, chess::Move move);

#endif