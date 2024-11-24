#include "../../include/utility/debug.hpp"

// Big Five
Debug::Debug():
    debugFile(std::make_unique<std::ofstream>("debug.txt", std::ios::app)) {
    if (!debugFile->is_open())
        std::cerr << "Failed to open debug.txt!" << std::endl;
}

Debug::~Debug() = default;

Debug& Debug::operator=(Debug&& other) noexcept {
    if (this != &other)
        debugFile = std::move(other.debugFile);
    return *this;
}
