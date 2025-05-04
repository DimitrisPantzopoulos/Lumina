#ifndef TT_H
#define TT_H

#include "..\ChessLib\chess-library\include\chess.hpp"

#include <cstdlib>
#include <vector>
#include <ctime> 
#include <algorithm>

#define BYTES_IN_A_MB 1048576
#define MAX_TT_SIZE_IN_MB 64
#define TT_ENTRY_SIZE 16

#define MAX_TT_SIZE (BYTES_IN_A_MB * MAX_TT_SIZE_IN_MB) / TT_ENTRY_SIZE

struct TTEntry {
    int value;                   // Evaluation score
    int depth;                   // Depth of the search when this position was evaluated
    int nodeType;                // Type of node (UPPERBOUND, EXACT, LOWERBOUND) (1, 2, 3) respectively
    chess::Move bestMove;        // Best move found from this position

    TTEntry() : value(0), depth(0), nodeType(1), bestMove(chess::Move::NO_MOVE) {}  // Default constructor

    TTEntry(int v, int d, int nt, chess::Move bm) : value(v), depth(d), nodeType(nt), bestMove(bm) {} // Constructor with values
};

struct TT{
    TT(){
        std::srand(457345);
    }
    
    std::unordered_map<uint64_t, TTEntry> TTable;

    void storeTTEntry(const uint64_t key, int value, int depth, int nodeType, chess::Move bestMove) {
        auto it = TTable.find(key);
    
        if (it != TTable.end()) {
            //If Key already exists but depth is higher overwrite it
            if (depth > it->second.depth) {
                TTEntry entry(value, depth, nodeType, bestMove);
                TTable[key] = entry;
            }
            
            // Check if TT is full
            if (TTable.size() >= MAX_TT_SIZE) {
                // Remove a random entry
                auto RandomEntry = std::next(TTable.begin(), std::rand() % TTable.size());
                TTable.erase(RandomEntry);
            }

        } else {
            TTEntry entry(value, depth, nodeType, bestMove);
            TTable[key] = entry;
        }
    }

    bool retrieveTTEntry(const uint64_t key, TTEntry &entry, int depth) {
        auto it = TTable.find(key);

        if (it != TTable.end()) {
            if(it->second.depth >= depth){
                entry = it->second;
                return true;
            }
        }

        return false;
    }

    void ClearTT(){
        TTable.clear();
    }
};

struct KM {
    int value;                      // Evaluation score
    int depth;                      // Depth of the search when this position was evaluated
    chess::Move KillerMove;         // Best move found from this position

    KM() 
        : value(0), depth(0), KillerMove(chess::Move::NO_MOVE) {} // Default constructor

    KM(int v, int d, chess::Move bm)
        : value(v), depth(d), KillerMove(bm) {}
};

struct KMEntry{
    std::array<KM, 2> KillerMovesForPly;

    KMEntry() : KillerMovesForPly{KM(), KM()} {} // Initialize with default null KM entries

    void addKillerMove(const chess::Move& CandidateKillerMove, const int CandidateScore, const int Ply) 
    {
        if(CandidateScore > KillerMovesForPly[0].value){
            // Swap to the first position as this is the best killer move
            KillerMovesForPly[1] = KillerMovesForPly[0];
            KillerMovesForPly[0] = KM(CandidateScore, Ply, CandidateKillerMove);

        } else if(CandidateScore > KillerMovesForPly[1].value){
            // Swap to the position[1] as this is the better killer move
            KillerMovesForPly[1] = KM(CandidateScore, Ply, CandidateKillerMove);
        }
    }

    chess::Movelist getKillerMoves()
    {
        chess::Movelist KM;

        KM.add(KillerMovesForPly[0].KillerMove);
        KM.add(KillerMovesForPly[1].KillerMove);

        return KM;
    }
};

struct KMT{
    std::vector<KMEntry> KillerMoveTable;

    void addKillerMoves(const chess::Move& CandidateKillerMove, const int CandidateScore, const int Ply){
        // Ensure that an entry exists
        if(KillerMoveTable.size() <= Ply){
            KillerMoveTable.resize(Ply + 1);
        }

        KillerMoveTable[Ply].addKillerMove(CandidateKillerMove, CandidateScore, Ply);
    }

    chess::Movelist getKillerMoves(const int Ply){
        //Ensure that an entry exists
        if(KillerMoveTable.size() <= Ply){
            KillerMoveTable.resize(Ply + 1);
        }

        return KillerMoveTable[Ply].getKillerMoves();
    }

    void ClearKMT(){
        KillerMoveTable.clear();
    }
};

struct HT{
    int16_t HistoryTable[2][64][64] = {};

    void Clear(){
        for (int color = 0; color < 2; ++color) {
            for (int from = 0; from < 64; ++from) {
                for (int to = 0; to < 64; ++to) {
                    HistoryTable[color][from][to] = 0;
                }
            }
        }
    }

    void Update(const bool Color, const chess::Move& Move, const int Depth, const bool CausedBetaCutoff){
        int16_t& ref = HistoryTable[Color][Move.from().index()][Move.to().index()];
        int bonus = Depth * Depth * (CausedBetaCutoff ? 1 : -1);
        ref += bonus - (ref * std::abs(bonus)) / 16384;
        ref = std::clamp(ref, static_cast<int16_t>(-32767), static_cast<int16_t>(32767));
    }

    int HistoryHeuristic(const bool Color, const chess::Move& Move){
        return HistoryTable[Color][Move.from().index()][Move.to().index()];
    }
};

#endif