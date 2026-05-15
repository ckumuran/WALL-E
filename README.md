<div align="center">

# ♟ CHESSKIDSDOTCOM

![Amateurs](assets/chessmaster.png)

*Yeah. Let's talk about what a real chess engine looks like.*

</div>

---

## What Is This

A chess engine. Written from scratch. In C++17.

Not "inspired by Stockfish." Not "following along with a YouTube series." Not "I copy-pasted the bitboard section and figured out the rest." From scratch — like, the pieces don't even know they're pieces until I told them what they are.

Will it beat Magnus Carlsen? No. Magnus doesn't lose to software he hasn't heard of. Will it beat you? Honestly, probably. Is that the point? Not really — the point was to understand how these things actually work and then build one without it looking like a crime scene. Mission accomplished.

---

## Why It's Interesting (Stay With Me)

Most chess engines fall into two categories:

1. Toy projects that technically move pieces but fold under any real position like a pawn on the seventh rank with no backup
2. Stockfish — which is incredible but reading that codebase is like trying to understand a language that hasn't been invented yet

This one lives in the middle. Real engineering, readable code, decisions you can actually follow. Think of it as the chess engine that shows its work.

---

## The Interesting Bits

Let's start with the foundation, because this is where most projects either nail it or produce something that technically compiles but spiritually doesn't.

**The type system actually means something** — [`types.h`](types.h):

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

That `~color` trick? That's flipping from White to Black — or Black to White — at compile time, zero cost, one character. It's the kind of thing that looks small until you're writing search code at 2am and you realize every other engine has a function called `getOpponent()` that does this with an if-statement. Not here.

The squares are laid out A1 through H8 in order so the index math just... works. No magic offsets. No "wait why is this 56." Square 0 through square 63. Chess grandmasters call this "board vision." We call it an enum.

**The transposition table entry has a diet** — [`tt.h`](tt.h):

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

Quick detour for the non-programmers: a transposition table is the engine's memory. When it sees a position it already evaluated — maybe through a different sequence of moves — it looks it up instead of redoing the work. Like recognizing you've been in this exact situation before and knowing it ends badly. Chess players call this "pattern recognition." We call it a hash table.

Now, `flag` and `age` are `uint8_t` instead of `int`. That's 1 byte each instead of 4. Doesn't sound dramatic until you have millions of these entries and suddenly your cache is doing backflips trying to keep up. Every byte you save here is real performance. No field in this struct is there by accident.

---

## How The Whole Thing Fits Together

### The Board (aka "Where Are The Pieces")

The board uses a hybrid setup: **bitboards** plus a **mailbox**.

Bitboards are just 64-bit integers where each bit represents a square. Want to know all the squares a bishop attacks from e4? It's a lookup and a couple of bitwise operations — no loops, no checking each square one by one. Just math. Fast math. The kind of math that doesn't care how complicated your position looks.

The mailbox is a plain array: ask it what's on square e4, it tells you immediately. The two approaches cover each other's weaknesses. It's the rook-and-bishop of data structures — individually fine, together unstoppable.

```cpp
U64 knightAttacks = KNIGHT_ATTACKS[sq];
U64 blockers = occupied & BISHOP_MASKS[sq];
U64 bishopAttacks = BISHOP_TABLE[sq][pext(blockers, BISHOP_MASKS[sq])];
```

### Move Generation (The Part That Has To Be Perfect)

[`movegen.cpp`](movegen.cpp) generates every move a piece can legally make — castling, en passant, promotions, all of it. This is the part where most from-scratch engines silently get things wrong and then wonder why their engine blunders a queen every few games.

This one is **perft-verified**. Perft is a test that counts the exact number of legal positions reachable after N moves from a given starting position. There are known correct counts for these — published, verified, canonical. If your number matches, your move generation is correct. Not "probably correct." Correct. The engine passed. Moving on.

```cpp
Move move = encodeMove(from, to, piece, flag);
Square from = moveFrom(move);
Square to   = moveTo(move);
```

Each move is a single 32-bit integer. Source square, destination, piece type, special flags — packed in. No objects, no heap allocation, just a number you can copy around for free. A pawn knows its promotion destination the same way a grandmaster knows the endgame: it's all already in there.

### Make/Unmake (The Tedious Part That Matters)

When the engine searches, it tries millions of moves and undoes them. Most engines take the simple approach: copy the entire board before each move, search, throw the copy away. Works great. Also wastes a lot of time copying things.

This engine uses **incremental make/unmake** — it tracks exactly what changed (piece moved, capture removed, castling rights updated, en passant square set) and reverses those exact changes. More code to write. Zero copying. At depth 8+ with millions of nodes per second, this stops being a micro-optimization and starts being the difference between fast and "why is this taking so long."

### Search (The Part That Actually Plays Chess)

[`search.cpp`](search.cpp) uses **alpha-beta search** — an algorithm that explores the game tree while cutting off branches that can't possibly improve the current best result. It's how you go from "evaluate every possible position" (impossible, there are more chess games than atoms in the universe, yes really) to "evaluate the positions that actually matter" (hard, but here we are).

The transposition table plugs in here: same position, different move order — looked up, not re-searched. **Zobrist hashing** ([`zobrist.cpp`](zobrist.cpp)) gives each board position a unique 64-bit fingerprint, updated incrementally as moves happen so you're never recomputing from scratch.

### UCI (The Part That Connects To The World)

[`uci.cpp`](uci.cpp) implements the Universal Chess Interface — the standard protocol for chess engines to talk to GUIs. Plug this into any UCI-compatible interface and it just works: receives positions, outputs moves, handles time controls. Unglamorous. Essential. Chess engines without UCI are like rooks with no open files — technically present, not doing much.

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

Flat structure. It's a small, clear project and nested directories would just be bureaucracy at this scale.

---

## Why

I like knowing how things actually work. Not "it uses alpha-beta search" — I mean actually knowing: what's in the struct, why the flag is a `uint8_t`, what happens when you unmake a castling move that involved an en passant capture. That level.

Chess engines are a great target for this because they're hard enough to be interesting and bounded enough to finish. Every component has a job. The jobs connect. The whole thing either plays chess or it doesn't — there's no partial credit.

It does. It plays chess. That's what I'm saying.

---

<div align="center">

♟ Built by [c.kumaran](https://github.com/c.kumaran)

</div>
