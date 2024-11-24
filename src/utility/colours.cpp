#include "../../include/utility/colours.hpp"

namespace Colours {
    // Background colour
    const raylib::Color DARK_BLUE = raylib::Color(44, 44, 127, 255);

    // Empty colour
    const raylib::Color DARK_GREY = raylib::Color(26, 31, 40, 255);

    // Score colour
    const raylib::Color ROYAL_BLUE = raylib::Color(59, 85, 162, 255);

    // Block colours
    const raylib::Color BLOCK_RED = raylib::Color(232, 18, 18, 255);
    const raylib::Color BLOCK_ORANGE = raylib::Color(227, 116, 17, 255);
    const raylib::Color BLOCK_YELLOW = raylib::Color(237, 234, 4, 255);
    const raylib::Color BLOCK_GREEN = raylib::Color(47, 230, 23, 255);
    const raylib::Color BLOCK_CYAN = raylib::Color(21, 204, 209, 255);
    const raylib::Color BLOCK_BLUE = raylib::Color(13, 64, 216, 255);
    const raylib::Color BLOCK_PURPLE = raylib::Color(166, 0, 247, 255);

    // Colour list
    const std::array<raylib::Color, NUM_COLOURS> COLOUR_LIST = {DARK_GREY, BLOCK_CYAN, BLOCK_BLUE, BLOCK_ORANGE, BLOCK_YELLOW, BLOCK_GREEN, BLOCK_PURPLE, BLOCK_RED};
}