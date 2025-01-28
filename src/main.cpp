#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include "../raylib-cpp/raylib-cpp.hpp"

#include "../include/game/game.hpp"
#include "../include/utility/inputparser.hpp"
#include "../include/utility/utility.hpp"

Debug debugLogger;

// Global mutable debug flags
bool debug = false;

i32 main(i32 argc, char* argv[]) {
    std::vector<String> validOptions = {"-h", "-help", "-d", "-debug"};
    String input;
    try {
        if (argc > 2)
            throw std::invalid_argument(std::format("Too many arguments. Argument count: {}", argc));
        else {
            InputParser ip(argc, argv, validOptions);
            if (ip.optionExists("-h") || ip.optionExists("-help")) {
                Utility::displayCredits();
                Utility::printHelp();
                return 0;
            } else if (
                #ifdef DEBUG
                true
                #else
                ip.optionExists("-d") || ip.optionExists("-debug")
                #endif
            ) {
                debug = true;
                std::ofstream file{"debug.txt", std::ios::trunc};
                if (!file)
                    std::println(stderr, "Error opening file for emptying.");
                else {
                    std::println(file, "==========BEGIN DEBUG LOG==========");
                    std::println(file, "Current time: {}", Utility::getCurrentTime());
                    std::println(file, "===================================");
                }
            }
        }
        f64 lastUpdateTime;
        raylib::Window window{GameInfo::WINDOW_WIDTH, GameInfo::WINDOW_HEIGHT, "Tetris"};
        window.SetIcon(Assets::GAME_ICON);
        const raylib::Font GAME_FONT = raylib::LoadFontEx("assets/font/vt323.ttf", 64, nullptr, 0);
        window.SetTargetFPS(60);
        Game g;
        while (!window.ShouldClose()) {
            UpdateMusicStream(g.music);
            if (Utility::eventTriggered(0.2, lastUpdateTime, window))
                g.movePieceDown();
            g.handleInput();
            window.BeginDrawing();
            if (debug)
                window.ClearBackground(BLUE);
            else
                window.ClearBackground(Colours::DARK_BLUE);
            g.drawScoreWord(GAME_FONT);
            g.drawScore(GAME_FONT);
            g.drawNext(GAME_FONT);
            if (g.getGameOverState())
                g.displayGameOver(GAME_FONT);
            g.drawGame();
            window.EndDrawing();
        }
    } catch (const std::invalid_argument& e) {
        std::println(stderr, "Invalid argument error: {}", e.what());
        return 1;
    } catch (const raylib::RaylibException& e) {
        std::println(stderr, "Graphics error: {}", e.what());
        return 2;
    } catch (const std::overflow_error& e) {
        std::println(stderr, "Overflow error: {}", e.what());
        return 3;
    } catch (const std::runtime_error& e) {
        std::println(stderr, "Runtime error: {}", e.what());
        return 4;
    } catch (const std::out_of_range& e) {
        std::println(stderr, "Range error: {}", e.what());
        return 5;
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 6;
    } catch (...) {
        std::println(stderr, "Unknown error");
        return -1;
    }
    return 0;
}
