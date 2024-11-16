#ifndef PST_H
#define PST_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <algorithm>
#include <map>

using namespace chess;
using namespace std;

float PST(const Piece &piece, int squareIndex, float& endgameWeight);

#endif