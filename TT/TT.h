#ifndef TT_H
#define TT_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include "../Lumina.h"
#include <vector>

struct TTEntry {
    int value;                   // Evaluation score
    int depth;                   // Depth of the search when this position was evaluated
    int nodeType;                // Type of node (upperbound, exact, lowerbound) (1, 2, 3) respectively
    chess::Move bestMove;        // Best move found from this position

    TTEntry() 
        : value(0.0f), depth(0), nodeType(1), bestMove(chess::Move::NO_MOVE) {}  // Default constructor

    TTEntry(int v, int d, int nt, chess::Move bm)
        : value(v), depth(d), nodeType(nt), bestMove(bm) {}
};

struct KM {
    float value;                    // Evaluation score
    int depth;                      // Depth of the search when this position was evaluated
    chess::Move KillerMove;         // Best move found from this position

    KM() 
        : value(0.0f), depth(0), KillerMove(chess::Move::NO_MOVE) {} // Default constructor

    KM(int v, int d, chess::Move bm)
        : value(v), depth(d), KillerMove(bm) {}
};

struct KMEntry{
    std::array<KM, 2> KillerMovesForPly;

    KMEntry() 
        : KillerMovesForPly{KM(), KM()} {} //Initialize with default KM entries

    void addKillerMove(const chess::Move& CandidateKillerMove, const int CandidateScore, const int Ply) {
        if(CandidateScore > KillerMovesForPly[0].value){
            //Swap to the first position as this is the best killer move
            KillerMovesForPly[1] = KillerMovesForPly[0];
            KillerMovesForPly[0] = KM(CandidateScore, Ply, CandidateKillerMove);

        } else if(CandidateScore > KillerMovesForPly[1].value){
            //Swap to the position[1] as this is the better killer move
            KillerMovesForPly[1] = KM(CandidateScore, Ply, CandidateKillerMove);
        }
    }

    chess::Movelist getKillerMoves(){
        chess::Movelist KM;

        KM.add(KillerMovesForPly[0].KillerMove);
        KM.add(KillerMovesForPly[1].KillerMove);

        return KM;
    }
};

struct KMT{
    std::vector<KMEntry> KillerMoveTable;

    void addKillerMoves(const chess::Move& CandidateKillerMove, const int CandidateScore, const int Ply){
        //Ensure that an entry exists
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

#endif