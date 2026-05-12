<div align="center">

# ♟ CHESSKIDSDOTCOM

### A modern chess engine written in C++17

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

<img src="./assets/chessmaster.png" width="280">

### I am the Chess Master.

</td>

<td align="center">

<img src="./assets/longarm.png" width="280">

### Take THAT !!

</td>

<td align="center">

<img src="./assets/monitorgod.png" width="280">

### “Amateurs.”

</td>

</tr>
</table>

</div>

---

# What is this?

`chesskidsdotcom` is a chess engine written from scratch in C++17.

The name comes from the website I used to play chess on growing up, so I kept it instead of giving it some serious engine name.

The project started because I wanted to understand how chess engines actually work internally.

Turns out chess engines and game engines in general are mostly:
- optimization
- recursion
- debugging
- move generation
- performance engineering

---

# Engine ( Brain ):
- bitboard move representation
- hybrid mailbox + bitboards
- packed 32-bit move encoding
- incremental make/unmake
- alpha-beta search
- transposition tables
- zobrist hashing
- move generation
- perft testing/debugging
- UCI communication
- modular engine structure

The engine can:
- understand chess positions
- generate legal moves
- search future positions
- evaluate positions
- and communicate with external chess GUIs.

---

<div align="center">

### ♞ Play. Learn. Give up. Repeat.

### Built by C. Kumaran

</div>
