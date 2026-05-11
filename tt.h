#pragma once
#include "types.h"
struct TTEntry {
    U64 key;
    Move bestMove;
    int depth;
    int score;
    uint8_t flag;
    uint8_t age;
};
class TranspositionTable {
public:
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
