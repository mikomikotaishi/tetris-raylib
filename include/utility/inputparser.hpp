#pragma once
#include <algorithm>
#include <cassert>
#include <format>
#include <string>
#include <stdexcept>
#include <vector>

#include "stdint.hpp"

class InputParser {
private:
    Vector<String> args;
    Vector<String> validOptions; // Optional
public:
    // Constructor
    InputParser(i32 argc, char* argv[]);
    InputParser(i32 argc, char* argv[], const Vector<String>& validOptions);

    // Methods
    String getOptionValue(const String& option) const;
    bool optionExists(const String& option) const;
};