#pragma once
#include "types.h"
inline constexpr U64 set_bit(U64 bb, Square sq) {
    return bb | (1ULL << sq);
}
inline constexpr U64 clear_bit(U64 bb, Square sq) {
    return bb & ~(1ULL << sq);
}
inline constexpr bool get_bit(U64 bb, Square sq) {
    return bb & (1ULL << sq);
}
inline int popcount(U64 bb) {
    return __builtin_popcountll(bb);
}
inline Square bitscan_forward(U64 bb) {
    return static_cast<Square>(__builtin_ctzll(bb));
}
inline Square pop_lsb(U64 &bb) {
    Square sq = bitscan_forward(bb);
    bb &= bb - 1;
    return sq;
}
