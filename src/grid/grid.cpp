#include "grid.hpp"

Grid::Grid():  
    grid{} 
    {}

void Grid::reinitialiseGrid() {
    for (usize i = 0; i < NUM_ROWS; ++i) for (usize j = 0; j < NUM_COLS; ++j) {
        grid[i][j] = 0;
    }
}

void Grid::drawGrid() const {
    for (usize i = 0; i < NUM_ROWS; ++i) for (usize j = 0; j < NUM_COLS; ++j) {
        int cellValue = grid[i][j];
        raylib::Rectangle cell = raylib::Rectangle(j * CELL_SIZE + GRID_OFFSET + 1, i * CELL_SIZE + GRID_OFFSET + 1, CELL_SIZE - 1, CELL_SIZE - 1);
        cell.Draw(COLOUR_LIST[cellValue]);
    }
}

bool Grid::isCellEmpty(u8 row, u8 column) const {
    assert(row < 20);
    assert(column < 10);
    return grid[row][column] == 0;
}

bool Grid::isCellOutside(u8 row, u8 column) const {
    return !((row >= 0) && (row < NUM_ROWS) && (column >= 0) && (column < NUM_COLS));
}

bool Grid::isRowFull(u8 row) const {
    assert(row < 20);
    for (usize column = 0; column < NUM_COLS; ++column)
        if (grid[row][column] == 0)
            return false;
    return true;
}

void Grid::clearRow(u8 row) {
    assert(row < 20);
    for (usize column = 0; column < NUM_COLS; ++column)
        grid[row][column] = 0;
}

void Grid::shiftRowDown(u8 row, u8 shift) {
    assert(row < 20);
    assert(row + shift < 20);
    for (usize column = 0; column < NUM_COLS; ++column) {
        grid[row + shift][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

u8 Grid::clearFullRows() {
    u8 completedRows = 0;
    for (i32 i = NUM_ROWS - 1; i >= 0; --i) { 
        if (isRowFull(i)) {
            if (debug)
                DEBUG << "Clearing row " << i << ".\n";
            clearRow(i);
            ++completedRows;
        } else if (completedRows > 0)
            shiftRowDown(i, completedRows);
    }
    if (debug)
        DEBUG << static_cast<i32>(completedRows) << " lines cleared.\n";
    return completedRows;
}

// Debug method
void Grid::printGrid() const {
    for (usize i = 0; i < NUM_ROWS; ++i) {
        for (usize j = 0; j < NUM_COLS; ++j)
            std::cout << grid[i][j] << " ";
        std::cout << std::endl;
    }
}

void Grid::setCell(u8 row, u8 col, u8 colourVal) {
    assert(row < 20);
    assert(col < 10);
    assert(colourVal >= 1 && colourVal <= 7);
    grid[row][col] = colourVal;
}