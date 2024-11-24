#include "../../include/piece/tetromino.hpp"

namespace RotationStates {
    const std::array<std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_I = {{
        {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)},
        {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)},
        {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)},
        {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)}
    }};

    const std::array<std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_J = {{
        {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)},
        {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)},
        {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)},
        {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)}
    }};

    const std::array<std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_L = {{
        {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)},
        {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)},
        {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)},
        {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)}
    }};

    const std::array<std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_O = {{
        {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)},
        {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)},
        {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)},
        {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}
    }};

    const std::array<std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_S = {{
        {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)},
        {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)},
        {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)},
        {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)}
    }};

    const std::array<std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_T = {{
        {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)},
        {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)},
        {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)},
        {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)}
    }};

    const std::array<std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES> ROTATION_STATES_Z = {{
        {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)},
        {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)},
        {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)},
        {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)}
    }};
}

IPiece::IPiece():
    Piece(PieceID::ID_I_PIECE, RotationStates::ROTATION_STATES_I) {
    movePiece(-1, 3);
}

JPiece::JPiece():
    Piece(PieceID::ID_J_PIECE, RotationStates::ROTATION_STATES_J) {
    movePiece(0, 3);
}

LPiece::LPiece():
    Piece(PieceID::ID_L_PIECE, RotationStates::ROTATION_STATES_L) {
    movePiece(0, 3);
}

OPiece::OPiece():
    Piece(PieceID::ID_O_PIECE, RotationStates::ROTATION_STATES_O) {
    movePiece(0, 4);
}

SPiece::SPiece():
    Piece(PieceID::ID_S_PIECE, RotationStates::ROTATION_STATES_S) {
    movePiece(0, 3);
}

TPiece::TPiece():
    Piece(PieceID::ID_T_PIECE, RotationStates::ROTATION_STATES_T) {
    movePiece(0, 3);
}

ZPiece::ZPiece():
    Piece(PieceID::ID_Z_PIECE, RotationStates::ROTATION_STATES_Z) {
    movePiece(0, 3);
}