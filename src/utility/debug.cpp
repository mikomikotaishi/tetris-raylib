#include "../../include/utility/debug.hpp"

// Big Five
Debug::Debug():
    debugFile(std::make_unique<std::ofstream>("debug.txt", std::ios::app)) {
    if (!debugFile->is_open())
        std::println("Failed to open debug.txt!");
}

Debug::~Debug() = default;

Debug& Debug::operator=(Debug&& other) noexcept {
    if (this != &other)
        debugFile = std::move(other.debugFile);
    return *this;
}
