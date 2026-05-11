#include "tt.h"
#include <cstring>
#include <vector>
static std::vector<TTEntry> table;
static size_t tableSize = 0;
void TranspositionTable::resize(size_t mb) {
    size_t bytes = mb * 1024ULL * 1024ULL;
    tableSize = bytes / sizeof(TTEntry);
    size_t pow2 = 1;
    while (pow2 < tableSize)
        pow2 <<= 1;
    tableSize = pow2;
    table.clear();
    table.resize(tableSize);
    clear();
}
void TranspositionTable::clear() {
    std::memset(
        table.data(),
        0,
        table.size() * sizeof(TTEntry)
    );
}
TTEntry* TranspositionTable::probe(U64 key) {
    return &table[key & (tableSize - 1)];
}
void TranspositionTable::store(
    U64 key,
    Move bestMove,
    int depth,
    int score,
    int flag
) {
    TTEntry* entry = probe(key);
    if (entry->key != key || depth >= entry->depth) {
        entry->key = key;
        entry->bestMove = bestMove;
        entry->depth = depth;
        entry->score = score;
        entry->flag = static_cast<uint8_t>(flag);
    }
}
