#include "..\ChessLib\chess-library\include\chess.hpp"
#include "../Lumina.h"
#include "TT.h"

void Lumina::ClearTT(){
    TT.ClearTT();
}

void Lumina::ClearKMT(){
    KillerMoveTable.ClearKMT();
}