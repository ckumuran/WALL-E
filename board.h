#pragma once
#include <array>
#include <string>
#include "types.h"
struct Board {
    U64 pieces[12];
    U64 occupancies[3];
    Piece mailbox[64];
    Color side;
    int castlingRights;
    Square epSquare;
    int halfmoveClock;
    int fullmoveNumber;
    U64 hash;
    void clear();
    bool parse_fen(const std::string& fen);
    std::string get_fen() const;
    void print() const;
};
