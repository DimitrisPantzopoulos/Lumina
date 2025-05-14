#pragma once

#include "..\ChessLib\chess.hpp"

#define BISHOPPAIR_MG 30
#define BISHOPPAIR_EG 40

constexpr std::array<float, 32> GenerateEndgameWeights() {
    std::array<float, 32> weights{};
    for (int pieces = 0; pieces < 32; pieces++) {
        weights[pieces] = static_cast<float>(pieces) / 32.0f;
    }
    return weights;
}

static constexpr std::array<float, 32> EndgameWeights = GenerateEndgameWeights();

inline float CalculateEndgameWeights(const int& PieceCount){
    return EndgameWeights[PieceCount];
}

inline int PrecomputedBishopValues(const int& PieceCount){
    static constexpr std::array<int, 17> BishopWeights = [] {
        std::array<int, 17> weights{};
 
        for (int pieces = 0; pieces <= 16; pieces++) {
            float weight = static_cast<float>(pieces) / 32.0f;
            weights[pieces] = static_cast<int>(weight * BISHOPPAIR_MG + (1 - weight) * BISHOPPAIR_EG);
        }

        return weights;
    }();

    return BishopWeights[PieceCount];
}

inline uint64_t PrecomputedForwardMasks(const int Rank, const bool isWhite) {
    static constexpr std::array<uint64_t, 8> WhitePawnMasks = [] {
        std::array<uint64_t, 8> masks{};
        for (int rank = 0; rank < 8; rank++) {
            masks[rank] = (rank < 7) ? (0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8)) : 0ULL;
        }
        return masks;
    }();

    static constexpr std::array<uint64_t, 8> BlackPawnMasks = [] {
        std::array<uint64_t, 8> masks{};
        for (int rank = 0; rank < 8; rank++) {
            masks[rank] = (rank > 0) ? (0xFFFFFFFFFFFFFFFFULL >> (rank * 8)) : 0ULL;
        }
        return masks;
    }();

    return isWhite ? WhitePawnMasks[Rank] : BlackPawnMasks[Rank];
}

inline uint64_t PrecomputedFlankFileMasks(const int File){
    static constexpr std::array<uint64_t, 8> FlankFileMasks = [] {
        std::array<uint64_t, 8> masks{};

        for (int File = 0; File < 8; File++) {
            uint64_t leftFileMask  = (File > 0) ? 0x0101010101010101ULL << (File - 1) : 0;
            uint64_t rightFileMask = (File < 7) ? 0x0101010101010101ULL << (File + 1) : 0;

            masks[File] = leftFileMask | rightFileMask;
        }
        return masks;
    }();

    return FlankFileMasks[File];
}

inline uint64_t PrecomputeKnightForward(const int Rank, const bool isWhite){
    static constexpr std::array<uint64_t, 8> WhiteKForward = [] {
        std::array<uint64_t, 8> masks{};
    
        for (int rank = 0; rank < 8; rank++) {
            masks[rank] = (rank < 7) ? ~0ULL << ((rank + 1) * 8) : 0ULL;
        }
    
        return masks;
    }();

    static constexpr std::array<uint64_t, 8> BlackKForward = [] {
        std::array<uint64_t, 8> masks{};

        for (int rank = 0; rank < 8; rank++) {
            masks[rank] = (rank < 7) ? 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8) : 0;
        }

        return masks;
    }();

    return isWhite ? WhiteKForward[Rank] : BlackKForward[Rank];
}

inline uint64_t PrecomputeKnightBackward(const int Rank, const bool isWhite){
    static constexpr std::array<uint64_t, 64> WhiteKBackward = [] {
        std::array<uint64_t, 64> masks{};

        for (int idx = 0; idx < 64; idx++) {
            masks[idx] = (idx >= 9 ? 0x5ULL << (idx - 9) : 0) & ~0x8181818181818181;;
        }

        return masks;
    }();

    static constexpr std::array<uint64_t, 64> BlackKBackward = [] {
        std::array<uint64_t, 64> masks{};

        for (int idx = 0; idx < 64; idx++) {
            masks[idx] = (idx <= 56 ? 0x5ULL << (idx + 7) : 0) & ~0x8181818181818181;
        }

        return masks;
    }();

    return isWhite ? WhiteKBackward[Rank] : BlackKBackward[Rank];
}

inline uint64_t ComputeFileMask(const int File){
    return 0x0101010101010101ULL << File;
}

inline uint64_t ComputeBForward(const int rank, const bool isWhite){
    return isWhite ? 0xFFFFFFFFFFFFFFFFULL << ((rank + 1) * 8) : 0xFFFFFFFFFFFFFFFFULL >> ((rank) * 8);
}