#include "../../include/grid/grid.hpp"

Grid::Grid():  
    grid{} 
    {}

void Grid::reinitialiseGrid() {
    for (usize i = 0; i < GameInfo::NUM_ROWS; ++i) for (usize j = 0; j < GameInfo::NUM_COLS; ++j) {
        #ifdef DEBUG
        grid.at(i).at(j) = 0;
        #else
        grid[i][j] = 0;
        #endif
    }
}

void Grid::drawGrid() const {
    for (usize i = 0; i < GameInfo::NUM_ROWS; ++i) for (usize j = 0; j < GameInfo::NUM_COLS; ++j) {
        #ifdef DEBUG
        i32 cellValue = grid.at(i).at(j);
        raylib::Rectangle cell = raylib::Rectangle(j * GameInfo::CELL_SIZE + GameInfo::GRID_OFFSET + 1, i * GameInfo::CELL_SIZE + GameInfo::GRID_OFFSET + 1, GameInfo::CELL_SIZE - 1, GameInfo::CELL_SIZE - 1);
        cell.Draw(Colours::COLOUR_LIST.at(cellValue));
        #else
        i32 cellValue = grid[i][j];
        raylib::Rectangle cell = raylib::Rectangle(j * GameInfo::CELL_SIZE + GameInfo::GRID_OFFSET + 1, i * GameInfo::CELL_SIZE + GameInfo::GRID_OFFSET + 1, GameInfo::CELL_SIZE - 1, GameInfo::CELL_SIZE - 1);
        cell.Draw(Colours::COLOUR_LIST[cellValue]);
        #endif
    }
}

bool Grid::isCellEmpty(u8 row, u8 column) const {
    #ifdef DEBUG
    assert(row < 20);
    assert(column < 10);
    return grid.at(row).at(column) == 0;
    #else 
    return grid[row][column] == 0;
    #endif
}

bool Grid::isCellOutside(u8 row, u8 column) const {
    return !((row >= 0) && (row < GameInfo::NUM_ROWS) && (column >= 0) && (column < GameInfo::NUM_COLS));
}

bool Grid::isRowFull(u8 row) const {
    #ifdef DEBUG
    assert(row < 20);
    #endif
    for (usize column = 0; column < GameInfo::NUM_COLS; ++column) {
        #ifdef DEBUG
        if (grid.at(row).at(column) == 0)
            return false;
        #else
        if (grid[row][column] == 0)
            return false;
        #endif
    }
    return true;
}

void Grid::clearRow(u8 row) {
    #ifdef DEBUG
    assert(row < 20);
    #endif
    for (usize column = 0; column < GameInfo::NUM_COLS; ++column) {
        #ifdef DEBUG
        grid.at(row).at(column) = 0;
        #else
        grid[row][column] = 0;
        #endif
    }
}

void Grid::shiftRowDown(u8 row, u8 shift) {
    #ifdef DEBUG
    assert(row < 20);
    assert(row + shift < 20);
    #endif
    for (usize column = 0; column < GameInfo::NUM_COLS; ++column) {
        #ifdef DEBUG
        grid.at(row + shift).at(column) = grid.at(row).at(column);
        grid.at(row).at(column) = 0;
        #else
        grid[row + shift][column] = grid[row][column];
        grid[row][column] = 0;
        #endif
    }
}

u8 Grid::clearFullRows() {
    u8 completedRows = 0;
    for (i32 i = GameInfo::NUM_ROWS - 1; i >= 0; --i) { 
        if (isRowFull(i)) {
            if (debug)
                std::println(debugLogger, "Clearing row {}.", i);
            clearRow(i);
            ++completedRows;
        } else if (completedRows > 0)
            shiftRowDown(i, completedRows);
    }
    if (debug)
        std::println(debugLogger, "{} lines cleared.", static_cast<i32>(completedRows));
    return completedRows;
}

// Debug method
void Grid::printGrid() const {
    for (usize i = 0; i < GameInfo::NUM_ROWS; ++i) {
        for (usize j = 0; j < GameInfo::NUM_COLS; ++j) {
            #ifdef DEBUG
            std::print("{} ", grid.at(i).at(j));
            #else
            std::print("{} ", grid[i][j]);
            #endif
        }
        std::print("\n");
    }
}

void Grid::setCell(u8 row, u8 col, u8 colourVal) {
    #ifdef DEBUG
    assert(row < 20);
    assert(col < 10);
    assert(colourVal >= 1 && colourVal <= 7);
    grid.at(row).at(col) = colourVal;
    #else
    grid[row][col] = colourVal;
    #endif
}