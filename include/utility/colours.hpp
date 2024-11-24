#pragma once

#include <array>
#include "../raylib-cpp/raylib-cpp.hpp"

#include "stdint.hpp"
#include "utility.hpp"

constexpr i32 NUM_COLOURS = 8;

// Background colour
extern const raylib::Color DARK_BLUE;

// Empty colour
extern const raylib::Color DARK_GREY;

// Score colour
extern const raylib::Color ROYAL_BLUE;

// Block colours
extern const raylib::Color BLOCK_RED;
extern const raylib::Color BLOCK_ORANGE;
extern const raylib::Color BLOCK_YELLOW;
extern const raylib::Color BLOCK_GREEN;
extern const raylib::Color BLOCK_CYAN;
extern const raylib::Color BLOCK_BLUE;
extern const raylib::Color BLOCK_PURPLE;

// Colour list
extern const std::array<raylib::Color, NUM_COLOURS> COLOUR_LIST;


