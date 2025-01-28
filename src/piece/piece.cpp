#include "../../include/piece/piece.hpp"

Piece::Piece(u8 id, const Array<Array<Position, GameInfo::NUM_TETROMINO_BLOCKS>, GameInfo::NUM_ROTATION_STATES>& cells):
    id{id}, rotationState{0}, cells{cells}, rowOffset{0}, columnOffset{0} {
    #ifdef DEBUG
    assert(id >= 1);
    assert(id <= 7);
    #endif
}

u8 Piece::getID() const {
    return id;
}

void Piece::drawPiece(i32 offsetX, i32 offsetY) const {
    Array<Position, GameInfo::NUM_TETROMINO_BLOCKS> tiles = getCellPositions();
    for (const Position& tile: tiles) {
        raylib::Rectangle cell = raylib::Rectangle(tile.getColumn() * GameInfo::CELL_SIZE + offsetX, tile.getRow() * GameInfo::CELL_SIZE + offsetY, GameInfo::CELL_SIZE - 1, GameInfo::CELL_SIZE - 1);
        #ifdef DEBUG
        cell.Draw(Colours::COLOUR_LIST.at(id));
        #else
        cell.Draw(Colours::COLOUR_LIST[id]);
        #endif
    }
}

// void Piece::drawPieceSmall() const {
     
// }

void Piece::movePiece(i8 rows, i8 columns) {
    #ifdef _DEBUG
    assert(rows >= -20);
    assert(rows < 20);
    assert(columns >= -10);
    assert(columns < 10);
    #endif
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

std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS> Piece::getCellPositions() const {
    #ifdef DEBUG
    Array<Position, GameInfo::NUM_TETROMINO_BLOCKS> tiles = cells.at(rotationState);
    #else
    Array<Position, GameInfo::NUM_TETROMINO_BLOCKS> tiles = cells[rotationState];
    #endif
    Array<Position, GameInfo::NUM_TETROMINO_BLOCKS> movedTiles;
    for (usize i = 0; i < GameInfo::NUM_TETROMINO_BLOCKS; ++i)  {
        #ifdef DEBUG
        Position newPos = Position(tiles.at(i).getRow() + rowOffset, tiles.at(i).getColumn() + columnOffset);
        movedTiles.at(i) = newPos;
        #else
        Position newPos = Position(tiles[i].getRow() + rowOffset, tiles[i].getColumn() + columnOffset);
        movedTiles[i] = newPos;
        #endif
    }
    return movedTiles;
}