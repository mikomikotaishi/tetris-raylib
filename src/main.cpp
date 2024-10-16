#include <filesystem>
#include <fstream>
#include <raylib-cpp.hpp>

#include "inputparser.hpp"
#include "game.hpp"
#include "utility.hpp"

Debug DEBUG;

// Global mutable debug flags
bool debug = false;

i32 main(i32 argc, char* argv[]) {
    std::vector<std::string> validOptions = {"-h", "-help", "-d", "-debug"};
    std::string input;
    try {
        if (argc > 2)
            throw std::invalid_argument("Too many arguments. Argument count: " + argc);
        else {
            InputParser ip(argc, argv, validOptions);
            if (ip.optionExists("-h") || ip.optionExists("-help")) {
                displayCredits();
                printHelp();
                return 0;
            } else if (ip.optionExists("-d") || ip.optionExists("-debug")) {
                debug = true;
                std::ofstream file{"debug.txt", std::ios::trunc};
                if (!file)
                    std::cerr << "Error opening file for emptying." << std::endl;
                else {
                    file << "==========BEGIN DEBUG LOG==========" << std::endl;
                    file << "Current time: " << getCurrentTime() << std::endl;
                    file << "===================================" << std::endl;
                }
            }
        }
        f64 lastUpdateTime;
        raylib::Window window{WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris"};
        window.SetIcon(GAME_ICON);
        const raylib::Font GAME_FONT = raylib::LoadFontEx("assets/font/vt323.ttf", 64, nullptr, 0);
        window.SetTargetFPS(60);
        Game g;
        while (!window.ShouldClose()) {
            UpdateMusicStream(g.music);
            if (eventTriggered(0.2, lastUpdateTime, window))
                g.movePieceDown();
            g.handleInput();
            window.BeginDrawing();
            if (debug)
                window.ClearBackground(BLUE);
            else
                window.ClearBackground(DARK_BLUE);
            g.drawScoreWord(GAME_FONT);
            g.drawScore(GAME_FONT);
            g.drawNext(GAME_FONT);
            if (g.getGameOverState())
                g.displayGameOver(GAME_FONT);
            g.drawGame();
            window.EndDrawing();
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument error: " << e.what() << std::endl;
        return 1;
    } catch (const raylib::RaylibException& e) {
        std::cerr << "Graphics error: " << e.what() << std::endl;
        return 2;
    } catch (const std::overflow_error& e) {
        std::cerr << "Overflow error: " << e.what() << std::endl;
        return 3;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 4;
    } catch (const std::out_of_range& e) {
        std::cerr << "Range error: " << e.what() << std::endl;
        return 5;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 6;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return -1;
    }
    return 0;
}
