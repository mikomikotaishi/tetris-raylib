#pragma once

#include "position.hpp"
#include "../utility/utility.hpp"

class Piece {
  private:
    u8 id;
    i8 rotationState;
    std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES> cells;
    i8 rowOffset;
    i8 columnOffset;
  protected:
    // Constructor
    Piece(u8 id, const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES>& cells);
  public:
    // Methods
    u8 getID() const;
    void drawPiece(i32 offsetX, i32 offsetY) const;
    void movePiece(i8 rows, i8 columns);
    void rotatePieceClockwise();
    void rotatePieceCounterclockwise();
    std::array<Position, NUM_TETROMINO_BLOCKS> getCellPositions() const;
};