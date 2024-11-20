#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "../Lumina.h"
#include "TT.h"

#define MAX_TT_SIZE 4194304 //64 MB limit

void Lumina::storeTTEntry(const uint64_t key, int value, int depth, int nodeType, chess::Move bestMove) {
    auto it = TT.find(key);
    
    if (it != TT.end()) {
        //If Key already exists but depth is higher overwrite it
        if (depth > it->second.depth) {
            TTEntry entry(value, depth, nodeType, bestMove);
            TT[key] = entry;
        }
        
        // Check if TT is full
        if (TT.size() >= MAX_TT_SIZE) {
            // Remove a random entry
            auto RandomEntry = std::next(TT.begin(), std::rand() % TT.size());
            TT.erase(RandomEntry);
        }

    } else {
        TTEntry entry(value, depth, nodeType, bestMove);
        TT[key] = entry;
    }
}

bool Lumina::retrieveTTEntry(const uint64_t key, TTEntry &entry, int depth) {
    auto it = TT.find(key);

    if (it != TT.end()) {
        if(it->second.depth >= depth){
            entry = it->second;
            return true;
        }
    }
    return false;
}

void Lumina::ClearTT(){
    TT.clear();
}

void Lumina::ClearKMT(){
    KillerMoveTable.ClearKMT();
}