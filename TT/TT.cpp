#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "../Lumina.h"
#include "TT.h"

void Lumina::ClearTT(){
    TT.ClearTT();
}

void Lumina::ClearKMT(){
    KillerMoveTable.ClearKMT();
}