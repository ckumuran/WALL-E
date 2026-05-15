<div align="center">

# ♟ CHESSKIDSDOTCOM

![Amateurs](assets/chessmaster.png)
</div>

---

## What Is This

A chess engine. Written from scratch in C++17.This one has bitboards, move generation, alpha-beta search, transposition tables, UCI protocol support — the whole deal. It's not gonna beat anyone good. But it beat me, and was enough for me.

There are 2 types of chess engines out there:
1, The ones that are basically a homework assignment with piece-moving logic. 
2. Stockfish, which is about 500,000-line codebase engine, that I could never understand let alone make.
This is neither. It's a chess engine with real data structures, real search, real performance thinking — that a normal person can make.

---

## My favorite parts

**The type system** — [`types.h`](types.h):

```cpp
enum Color { WHITE, BLACK, BOTH, NO_COLOR };

inline constexpr Color operator~(Color c) {
    return c == WHITE ? BLACK : WHITE;
}

enum Square {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    SQ_NONE
};
```

`~color` flips White to Black at compile time with one character. No function, no branching, no nothing. The squares are numbered A1 through H8 in order so the math always makes sense. This is the stuff that makes the rest of the codebase understandable.

**The transposition table entry** — [`tt.h`](tt.h):

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

A transposition table is like the engine's memory — when it hits a position it's already seen, it looks up the answer instead of re-doing the work. You end up with millions of these entries sitting in memory, so `flag` and `age` are `uint8_t` (1 byte) instead of `int` (4 bytes). 

---

## How It Works

### The Board

Hybrid bitboard and mailbox/address setup. A bitboard is a 64-bit integer where each bit is a square on the board — so "all squares a knight on f3 attacks" is just a precomputed number you look up. Fast. The mailbox/address is an array that tells you what piece is on any given square instantly. They work together.

```cpp
U64 knightAttacks = KNIGHT_ATTACKS[sq];
U64 blockers = occupied & BISHOP_MASKS[sq];
U64 bishopAttacks = BISHOP_TABLE[sq][pext(blockers, BISHOP_MASKS[sq])];
```

### Move Generation

[`movegen.cpp`](movegen.cpp) generates all the legal moves from any position — castling, promotions, everything. Getting this right is the part that makes or breaks an engine. A lot of engines have subtle bugs here that just silently produce wrong play forever.
This one is perft-verified. Perft counts the exact number of reachable positions after N moves.

```cpp
Move move = encodeMove(from, to, piece, flag);
Square from = moveFrom(move);
Square to   = moveTo(move);
```

Every move is a single 32-bit integer with everything packed in — where it's moving from, where it's going, what piece, any special flags. No allocations, no objects, just a number. Millions of these get generated and thrown away during search. 

### Make/Unmake moves

The engine searches by trying moves and undoing them, millions of times per second. Most engines just copy the board before each move and trash the copy when done. Simpler to write, wastes time copying.
This uses incremental make/unmake — tracks exactly what changed and reverses it.

### Search

Alpha-beta search ([`search.cpp`](search.cpp)) — explores the game tree and cuts branches that can't beat what we already found. The transposition table means positions we've already evaluated get looked up, not re-searched. Zobrist hashing ([`zobrist.cpp`](zobrist.cpp)) gives every position a unique 64-bit fingerprint updated in real time so lookups are fast.

### UCI

[`uci.cpp`](uci.cpp) is the Universal Chess Interface — the standard that lets engines talk to GUIs. 

---

## Demo

This is it running — board display, UCI handshake, depth 5 search on the King's Knight opening, and perft 4 counting 197,281 nodes in 1.2 seconds.

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

---

<div align="center">

Built by C.Kumaran ♟ 

</div>
