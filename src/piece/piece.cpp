#include "piece.hpp"

Piece::Piece(u8 id, const std::array<std::array<Position, NUM_TETROMINO_BLOCKS>, NUM_ROTATION_STATES>& cells):
    id{id}, rotationState{0}, cells{cells}, rowOffset{0}, columnOffset{0} {
    assert(id >= 1);
    assert(id <= 7);
}

u8 Piece::getID() const {
    return id;
}

void Piece::drawPiece(i32 offsetX, i32 offsetY) const {
    std::array<Position, NUM_TETROMINO_BLOCKS> tiles = getCellPositions();
    for (const Position& tile: tiles) {
        raylib::Rectangle cell = raylib::Rectangle(tile.getColumn() * CELL_SIZE + offsetX, tile.getRow() * CELL_SIZE + offsetY, CELL_SIZE - 1, CELL_SIZE - 1);
        cell.Draw(COLOUR_LIST[id]);
    }
}

void Piece::movePiece(i8 rows, i8 columns) {
    assert(rows >= -20);
    assert(rows < 20);
    assert(columns >= -10);
    assert(columns < 10);
    rowOffset += rows;
    columnOffset += columns;
}

void Piece::rotatePieceClockwise() {
    ++rotationState;
    if (static_cast<u64>(rotationState) == cells.size())
        rotationState = 0;
}

void Piece::rotatePieceCounterclockwise() {
    --rotationState;
    if (rotationState == -1)
        rotationState = cells.size() - 1;
}

std::array<Position, NUM_TETROMINO_BLOCKS> Piece::getCellPositions() const {
    std::array<Position, NUM_TETROMINO_BLOCKS> tiles = cells[rotationState];
    std::array<Position, NUM_TETROMINO_BLOCKS> movedTiles;
    for (usize i = 0; i < NUM_TETROMINO_BLOCKS; ++i)  {
        Position newPos = Position(tiles[i].getRow() + rowOffset, tiles[i].getColumn() + columnOffset);
        movedTiles[i] = newPos;
    }
    return movedTiles;
}