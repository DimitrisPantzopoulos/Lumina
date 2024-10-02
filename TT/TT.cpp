#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "../Dimibot.h"
#include "TT.h"

void Dimibot::storeTTEntry(const uint64_t key, int value, int depth, int nodeType, chess::Move bestMove) {
    auto it = TT.find(key);
    
    if (it != TT.end()) {
        //If Key already exists but depth is higher overwrite it
        if (depth > it->second.depth) {
            TTEntry entry(value, depth, nodeType, bestMove);
            TT[key] = entry;
        }

    } else {
        TTEntry entry(value, depth, nodeType, bestMove);
        TT[key] = entry;
    }
}

bool Dimibot::retrieveTTEntry(const uint64_t key, TTEntry &entry, int depth) {
    auto it = TT.find(key);

    if (it != TT.end()) {
        if(it->second.depth >= depth){
            entry = it->second;
            return true;
        }
    }
    return false;
}

void Dimibot::ClearTT(){
    TT.clear();
}
