#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

class Debug {
  private:
    std::unique_ptr<std::ofstream> debugFile;
  public:
    // Big Five
    Debug();
    ~Debug();
    Debug& operator=(Debug&& other) noexcept;
    // Methods
    template<typename T>
    Debug& operator<<(const T& message);
};

template<typename T>
Debug& Debug::operator<<(const T& message) {
    if (debugFile && debugFile->is_open()) {
        *debugFile << message;
        debugFile->flush();
    }
    return *this;
}

extern Debug DEBUG;
