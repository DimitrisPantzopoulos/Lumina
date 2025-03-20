#ifndef PST_H
#define PST_H

#include "..\ChessLib\chess-library\include\chess.hpp"
#include <algorithm>
#include <map>

using namespace chess;
using namespace std;

int PST(const int& PieceType, const bool PieceColor, int SquareIndex, float EndgameWeight);

#endif