#pragma once

#include "piece.hpp"

constexpr u8 ID_I_PIECE = 1;
constexpr u8 ID_J_PIECE = 2;
constexpr u8 ID_L_PIECE = 3;
constexpr u8 ID_O_PIECE = 4;
constexpr u8 ID_S_PIECE = 5;
constexpr u8 ID_T_PIECE = 6;
constexpr u8 ID_Z_PIECE = 7;

extern const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> ROTATION_STATES_I;
extern const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> ROTATION_STATES_J;
extern const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> ROTATION_STATES_L;
extern const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> ROTATION_STATES_O;
extern const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> ROTATION_STATES_S;
extern const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> ROTATION_STATES_T;
extern const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> ROTATION_STATES_Z;

class IPiece: public Piece {
  public:
    // Constructor
    IPiece();
};

class JPiece: public Piece {
  public:
    // Constructor
    JPiece();
};

class LPiece: public Piece {
  public:
    // Constructor
    LPiece();
};

class OPiece: public Piece {
  public:
    // Constructor
    OPiece();
};

class SPiece: public Piece {
  public:
    // Constructor
    SPiece();
};

class TPiece: public Piece {
  public:
    // Constructor
    TPiece();
};

class ZPiece: public Piece {
  public:
    // Constructor
    ZPiece();
};