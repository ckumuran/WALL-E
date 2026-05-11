#pragma once
#include <cstddef>
#include <cstdint>
#include "types.h"
enum TTFlag {
    TT_ALPHA,
    TT_BETA,
    TT_EXACT
};
struct TTEntry {
    U64 key = 0ULL;
    Move bestMove = 0;
    int depth = 0;
    int score = 0;
    uint8_t flag = TT_ALPHA;
    uint8_t age = 0;
};
class TranspositionTable {
public:
    TranspositionTable() = default;
    void resize(size_t mb);
    void clear();
    TTEntry* probe(U64 key);
    void store(
        U64 key,
        Move bestMove,
        int depth,
        int score,
        int flag
    );
};
extern TranspositionTable TT;
