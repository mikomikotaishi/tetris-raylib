#pragma once

#include <cassert>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <print>
#include <string>

#include "debug.hpp"
#include "colours.hpp"
#include "stdint.hpp"

namespace GameInfo {
    // Game resolution constants
    constexpr i32 GAME_HEIGHT = 600;
    constexpr i32 GAME_WIDTH = 300;
    constexpr i32 WINDOW_HEIGHT = 620;
    constexpr i32 WINDOW_WIDTH = 500;
    constexpr i32 GRID_OFFSET = 10;

    // Grid constants
    constexpr i32 CELL_SIZE = 30;
    constexpr i32 NUM_COLS = 10;
    constexpr i32 NUM_ROWS = 20;

    // Tetromino constants
    constexpr i32 NUM_PIECES = 7;
    constexpr i32 NUM_ROTATION_STATES = 4;
    constexpr i32 NUM_TETROMINO_BLOCKS = 4;
}

namespace Utility {
    void displayCredits();
    void printHelp();
    std::string getCurrentTime();
}