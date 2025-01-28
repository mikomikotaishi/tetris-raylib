#pragma once

#include "piece.hpp"

namespace PieceID {
    constexpr u8 ID_I_PIECE = 1;
    constexpr u8 ID_J_PIECE = 2;
    constexpr u8 ID_L_PIECE = 3;
    constexpr u8 ID_O_PIECE = 4;
    constexpr u8 ID_S_PIECE = 5;
    constexpr u8 ID_T_PIECE = 6;
    constexpr u8 ID_Z_PIECE = 7;
}

namespace RotationStates {
    extern const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_I;
    extern const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_J;
    extern const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_L;
    extern const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_O;
    extern const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_S;
    extern const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_T;
    extern const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_Z;
}

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