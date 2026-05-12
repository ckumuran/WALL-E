<div align="center">

# ♟ chesskidsdotcom

### A modern bitboard chess engine written in C++17

Bitboards • Alpha-Beta Search • Transposition Tables • UCI • Incremental Hashing

<br>

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![Bitboards](https://img.shields.io/badge/Board-Bitboards-purple)
![UCI](https://img.shields.io/badge/Protocol-UCI-green)
![Status](https://img.shields.io/badge/status-WIP-lightgrey)

</div>

---

## Why "chesskidsdotcom"?

I grew up playing chess online as a kid.

This project started as curiosity and slowly turned into a deep dive into:
- chess engine architecture
- move generation
- hashing
- search optimization
- low-level systems programming
- and classical engine design.

---

<div align="center">
  <img src="./assets/chessmaster.png" width="750">
</div>

---

# ✨ Current Features

- Bitboard board representation
- Hybrid mailbox + bitboards
- Packed 32-bit move encoding
- Incremental make/unmake
- Zobrist hashing
- Alpha-beta framework
- Transposition table framework
- UCI protocol support
- Perft framework
- Debug validation tools

---

# 🧠 Architecture

```text
src/
├── attacks.cpp
├── board.cpp
├── debug.cpp
├── eval.cpp
├── makemove.cpp
├── movegen.cpp
├── perft.cpp
├── search.cpp
├── tt.cpp
├── uci.cpp
├── zobrist.cpp
└── main.cpp
```

---

<div align="center">
  <img src="./assets/longarm.png" width="750">
</div>

---

# ⚙ Engine Design

The engine follows a classical architecture inspired by:

- Stockfish
- Ethereal
- Crafty
- Fruit
- Berserk

Core principles:
- cache-friendly layouts
- deterministic search
- minimal heap allocations
- incremental updates
- reversible make/unmake
- bitboard-first move generation

---

# 🚀 Planned Features

## Move Generation
- Magic bitboards
- Legal move filtering
- Pin detection
- Check evasions
- Castling legality
- En passant legality

## Search
- Iterative deepening
- Quiescence search
- Killer/history heuristics
- Null move pruning
- Late move reductions
- Aspiration windows

## Evaluation
- Piece-square tables
- Tapered evaluation
- Mobility scoring
- Pawn structure analysis
- King safety
- Passed pawns

## Future
- NNUE experimentation
- Endgame tablebases
- SMP threading
- Search tuning

---

# 🔨 Build

## Release

```bash
make
./chesskidsdotcom
```

## Debug

```bash
make debug
```

---

# 🖥 UCI

```text
uci
isready
position startpos
go depth 6
quit
```

Compatible with:
- CuteChess
- Arena
- BanksiaGUI
- ChessBase

---

<div align="center">
  <img src="./assets/monitorgod.png" width="750">
</div>

---

# 📊 Current Status

The engine is currently under active development.

Core architecture is implemented while:
- legal move generation
- search optimization
- evaluation tuning
- and full perft validation

are still in progress.

---

# 📁 Repository Structure

```text
.
├── assets/
├── attacks.cpp
├── attacks.h
├── bitboard.h
├── board.cpp
├── board.h
├── debug.cpp
├── debug.h
├── eval.cpp
├── eval.h
├── main.cpp
├── makemove.cpp
├── makemove.h
├── move.h
├── movegen.cpp
├── movegen.h
├── perft.cpp
├── perft.h
├── search.cpp
├── search.h
├── tt.cpp
├── tt.h
├── types.h
├── uci.cpp
├── uci.h
├── zobrist.cpp
└── zobrist.h
```

---

# 📚 Inspirations

- Stockfish
- Ethereal
- Berserk
- Crafty
- Fruit

---

# ⚠ Disclaimer

This is a personal systems-programming project focused on:
- chess engine architecture
- search algorithms
- optimization
- and low-level performance engineering.

The engine is still a work in progress.

---

<div align="center">

### ♞ Play. Learn. Debug. Repeat.

</div>
