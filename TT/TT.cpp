#include "..\ChessLib\chess-library\include\chess.hpp"
#include "../Lumina.h"
#include "TT.h"

void Lumina::ClearTT(){
    TranspositionTable.ClearTT();
}

void Lumina::ClearKMT(){
    KillerMoveTable.ClearKMT();
}

void Lumina::ClearHT(){
    HistoryTable.Clear();
}