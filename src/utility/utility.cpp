#include "../../include/utility/utility.hpp"

namespace Utility {
    void displayCredits() {
        std::println("Created by me :)");
    }

    void printHelp() {
        std::println("Help message");
    }

    std::string getCurrentTime() {
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm* nowTM = std::localtime(&nowTime);
        std::ostringstream oss;
        oss << std::put_time(nowTM, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
}