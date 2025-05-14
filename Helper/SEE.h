#ifndef SEE_H
#define SEE_H

#include "..\ChessLib\chess.hpp"
#include "..\Evaluation\Eval.h"
#include "HelperFunctions.h"

#include <vector>

bool SEE(const chess::Board& board, const chess::Move& move, const int Threshold);

#endif