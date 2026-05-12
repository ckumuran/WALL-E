# CHESSKIDSDOTCOM ♟

### A modern bitboard chess engine written in C++17

<br>

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![Bitboards](https://img.shields.io/badge/Bitboards-purple)
![UCI](https://img.shields.io/badge/UCI-green)
![AlphaBeta](https://img.shields.io/badge/Alpha--Beta-orange)
![Perft](https://img.shields.io/badge/Perft-Verified-brightgreen)
![Status](https://img.shields.io/badge/status-work%20in%20progress-lightgrey)

</div>

---

<div align="center">

<table>
<tr>
<td align="center">

<img src="./assets/chessmaster.png" width="320">

### How it started

> “I’ll just make a simple chess engine.”

</td>

<td align="center">

<img src="./assets/longarm.png" width="320">

### The middle

Bitboards, make/unmake,  
and a lot of debugging.

</td>

<td align="center">

<img src="./assets/monitorgod.png" width="320">

### The goal

Strong engine.  
Good vibes.

</td>
</tr>
</table>

</div>

---

# 🚀 Features

<table>
<tr>
<td>

- ✅ Bitboard board representation
- ✅ Incremental make/unmake
- ✅ Zobrist hashing
- ✅ Packed 32-bit move encoding
- ✅ Transposition table framework
- ✅ UCI support

</td>

<td>

- ✅ Alpha-beta framework
- ✅ Perft framework
- ✅ Debug validation tools
- 🚧 Magic bitboards
- 🚧 Legal move filtering
- 🚧 Evaluation tuning

</td>
</tr>
</table>

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

# ⚙ Engine Design

Inspired by classical engines such as:

- Stockfish
- Ethereal
- Fruit
- Crafty
- Berserk

Core principles:
- cache-friendly layouts
- deterministic search
- incremental updates
- reversible make/unmake
- bitboard-first move generation
- minimal heap allocations

---

# 📈 Roadmap

| Core | Search | Evaluation | Future |
|---|---|---|---|
| ✅ Board representation | 🚧 Iterative deepening | 🚧 PSTs | 🚧 NNUE |
| ✅ Zobrist hashing | 🚧 Quiescence search | 🚧 Mobility | 🚧 SMP |
| ✅ Make / unmake | 🚧 Killer heuristics | 🚧 King safety | 🚧 Tablebases |
| 🚧 Move generation | 🚧 LMR | 🚧 Pawn structure | 🚧 Tuning |
| 🚧 Legal filtering | 🚧 Null move pruning | 🚧 Tapered eval | 🚧 Optimization |

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
- Fruit
- Crafty

---

# ⚠ Disclaimer

This is a personal systems-programming project focused on:
- chess engine architecture
- search algorithms
- optimization
- and low-level performance engineering.

The engine is still under active development.

---

<div align="center">

### ♞ Play. Learn. Debug. Repeat.

</div>
