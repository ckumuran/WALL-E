<div align="center">

# ♟ CHESSKIDSDOTCOM

![Amateurs](assets/chessmaster.png)

</div>

---

## What I Built

This is a chess engine written from scratch in C++17. Not "chess engine inspired by Stockfish" or "chess engine with help from tutorials." From scratch — bitboards, move generation, alpha-beta search, transposition tables, UCI protocol, the whole thing. It's not going to beat Magnus. That was never the point. The point was to understand exactly how a chess engine works at every level, and then build one cleanly.

---

## Why It's Interesting

Most chess engines are either toy projects or incomprehensible performance monsters. This one sits in the middle: real engineering decisions, clean code, no magic numbers and no apologies.

**The type system is doing real work** ([`types.h`](types.h)):

```cpp
enum Color { WHITE, BLACK, BOTH, NO_COLOR };

inline constexpr Color operator~(Color c) {
    return c == WHITE ? BLACK : WHITE;
}

enum Square {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    // ... through H8
    SQ_NONE
};
```

`~color` flipping inline at compile time, squares laid out so the index math is obvious, pieces enumerated in a way that makes color queries trivial. This isn't boilerplate — it's the foundation everything else builds on.

**The transposition table entry is thinking about cache lines** ([`tt.h`](tt.h)):

```cpp
struct TTEntry {
    U64 key = 0ULL;
    Move bestMove = 0;
    int depth = 0;
    int score = 0;
    uint8_t flag = TT_ALPHA;
    uint8_t age = 0;
};
```

`flag` and `age` packed into `uint8_t` instead of `int`. That's not accidental — you want TT entries small because you're going to have millions of them and cache misses are death. Every field earns its place.

---

## How It Works

### Board Representation

Hybrid bitboard + mailbox. Bitboards ([`bitboard.h`](bitboard.h)) give you fast bulk operations — all the squares a bishop attacks, all the pawns on a file, piece presence queries. The mailbox gives you fast "what piece is on this square" lookups without scanning bits. Neither alone is as good as both together.

```cpp
// Bitboard operations are just integer math
U64 knightAttacks = KNIGHT_ATTACKS[sq];
U64 blockers = occupied & BISHOP_MASKS[sq];
U64 bishopAttacks = BISHOP_TABLE[sq][pext(blockers, BISHOP_MASKS[sq])];
```

### Move Generation

[`movegen.cpp`](movegen.cpp) generates pseudo-legal moves — all moves a piece could make ignoring check — then [`makemove.cpp`](makemove.cpp) validates legality. Perft-verified against known position node counts, so the move generation is correct. Not "probably correct." Correct.

```cpp
// Packed 32-bit move encoding — from, to, piece, flags in one integer
// No heap allocation, no indirection, just a number
Move move = encodeMove(from, to, piece, flag);
Square from = moveFrom(move);
Square to   = moveTo(move);
```

### Make/Unmake

Most engines copy the board state before each move (copy-make). This one uses incremental make/unmake — it tracks exactly what changed and reverses it. More code to write, but it means the search never copies a full board. At depth 8+ with millions of nodes, that matters.

### Search

Alpha-beta with a transposition table ([`search.cpp`](search.cpp), [`tt.h`](tt.h)). The TT stores the best move and score for positions we've already evaluated, so when the same position arises through a different move order, we skip the work. Zobrist hashing ([`zobrist.cpp`](zobrist.cpp)) gives each position a fast, incrementally-updated 64-bit key.

### UCI

[`uci.cpp`](uci.cpp) implements the Universal Chess Interface protocol. Hook it up to any UCI-compatible GUI and it works. That part's not glamorous but it's what makes it a real engine rather than a toy.

---

## Demo

<div align="center">

![Engine in action](assets/finaloutput.png)

</div>

---

## File Map

```
types.h          — enums, operator overloading, foundational types
bitboard.h       — bitboard typedefs and operations
board.cpp/h      — board state, Zobrist keys, position setup
attacks.cpp/h    — precomputed attack tables
movegen.cpp/h    — move generation
makemove.cpp/h   — incremental make/unmake
search.cpp/h     — alpha-beta search
eval.cpp/h       — static evaluation
tt.h             — transposition table
zobrist.cpp/h    — Zobrist hashing
uci.cpp/h        — UCI protocol
perft.cpp/h      — move generation testing
main.cpp         — entry point
```

Flat structure. It's a small project and the clarity is worth more than nested directories.

---

## Why

Built because I like understanding how things work at the bottom. Chess engines sit at an interesting intersection — bit manipulation, search algorithms, careful memory layout, a protocol that connects to real tooling. Good problem. Worth building from scratch.

This is what that looks like.

---

<div align="center">

♟ Built by [c.kumaran](https://github.com/c.kumaran)

</div>
