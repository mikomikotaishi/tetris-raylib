#include "../../include/piece/piece.hpp"

Position::Position(): 
    row{0}, column{0}
    {}

Position::Position(u8 row, u8 column): 
    row{row}, column{column} {}

u8 Position::getRow() const {
    return row;
}

u8 Position::getColumn() const {
    return column;
}

void Position::setRow(u8 newRow) {
    #ifdef DEBUG
    assert(newRow < 20);
    #endif
    row = newRow;
}

void Position::setColumn(u8 newColumn) {
    #ifdef DEBUG
    assert(newColumn < 10);
    #endif
    column = newColumn;
}