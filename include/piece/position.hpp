#pragma once

#include "../utility/utility.hpp"

class Position {
private:
    u8 row;
    u8 column;
public:
    // Constructor
    Position();
    Position(u8 row, u8 column);
    // Methods
    u8 getRow() const;
    u8 getColumn() const;
    void setRow(u8 newRow);
    void setColumn(u8 newRow);
};
