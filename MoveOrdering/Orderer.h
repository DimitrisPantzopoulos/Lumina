#ifndef ORDERMOVES_H
#define ORDERMOVES_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "..\Evaluation\Eval.h"
#include "..\Helper\SEE.h"
#include <algorithm>
#include <vector>

chess::Movelist OrderMoves(chess::Board& board, chess::Move& BestMove);
chess::Movelist OrderCaptures(chess::Board& board);

#endif