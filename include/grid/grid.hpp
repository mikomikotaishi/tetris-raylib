#pragma once

#include <array>
#include <iostream>

#include "../utility/utility.hpp"

extern bool debug;

class Grid {
  private:
    std::array<std::array<u8, NUM_COLS>, NUM_ROWS> grid;
    void clearRow(u8 row);
    void shiftRowDown(u8 row, u8 numRows);
  public:
    // Constructor
    Grid();
    // Methods
    void reinitialiseGrid();
    void drawGrid() const;
    bool isCellOutside(u8 row, u8 iolumn) const;
    bool isCellEmpty(u8 row, u8 column) const;
    bool isRowFull(u8 row) const;
    u8 clearFullRows();
    // Debug
    void printGrid() const;
    void setCell(u8 row, u8 col, u8 colourVal);
};