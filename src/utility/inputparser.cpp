#include "../../include/utility/inputparser.hpp"

bool isInteger(const String& s) {
    try {
        std::stoi(s);
        return true;
    } catch (...) {
        return false;
    }
}
 
// Constructor
InputParser::InputParser(i32 argc, char* argv[]) {
    for (i32 i = 1; i < argc; ++i) 
        args.push_back(String(argv[i]));
}

InputParser::InputParser(i32 argc, char* argv[], const Vector<String>& validOptions): 
    validOptions(validOptions) {
    #ifdef DEBUG
    assert(argc >= 1);
    #endif
    bool foundValue = false;
    for (i32 i = 1; i < argc; ++i) 
        args.push_back(std::string(argv[i]));
    for (const std::string& arg: args) {
        if (std::find(validOptions.begin(), validOptions.end(), arg) == validOptions.end()) {
            if (isInteger(arg) && !foundValue) {
                foundValue = true;
                continue;
            }
            throw std::invalid_argument(std::format("Invalid option: {}", arg));
        }
    }
}

// Methods
std::string InputParser::getOptionValue(const String& option) const {
    Vector<String>::const_iterator it = std::find(args.begin(), args.end(), option);
    if (it != args.end() && ++it != args.end()) 
        return *it;
    return "";
}

bool InputParser::optionExists(const String& option) const {
    return std::find(args.begin(), args.end(), option) != args.end();
}