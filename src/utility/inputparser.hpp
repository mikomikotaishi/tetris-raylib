#pragma once
#include <algorithm>
#include <string>
#include <stdexcept>
#include <vector>

#include "stdint.hpp"

class InputParser {
  private:
    std::vector<std::string> args;
    std::vector<std::string> validOptions; // Optional
  public:
    // Constructor
    InputParser(i32 argc, char* argv[]);
    InputParser(i32 argc, char* argv[], const std::vector<std::string>& validOptions);

    // Methods
    std::string getOptionValue(const std::string& option) const;
    bool optionExists(const std::string& option) const;
};