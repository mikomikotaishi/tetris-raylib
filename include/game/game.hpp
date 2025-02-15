#pragma once

#include <print>
#include <random>

#include "../grid/grid.hpp"
#include "../piece/tetromino.hpp"
#include "../utility/assets.hpp"
#include "../utility/colours.hpp"

extern bool debug;

namespace Utility {
    bool eventTriggered(f64 interval, f64& lastUpdateTime, const raylib::Window& window);
}

namespace GameRectangles {
    const raylib::Rectangle SCORE_RECTANGLE = raylib::Rectangle(320, 55, 170, 60);
    const raylib::Rectangle NEXT_RECTANGLE = raylib::Rectangle(320, 215, 170, 180);
}

class Game {
private:
    Grid g;
    bool gameOver = false;
    Vector<Piece> pieces;
    std::mt19937 gen;
    u16 level = 1;
    i32 score = 0;
    Piece currentPiece;
    Piece nextPiece;
    Sound clearSound;
    Sound rotateSound;
    // Methods
    void resetGame();
    bool isPieceOutside() const;
    void movePieceLeft();
    void movePieceRight();
    void lockPiece();
    bool pieceFits() const;
    void slamPiece();
    void rotatePieceClockwise();
    void rotatePieceCounterclockwise();
    void updateScore(u8 linesCleared, u8 movedDown);
public:
    raylib::Music music;
    // Constructor
    Game();
    // Destructor
    ~Game();
    // Methods
    bool getGameOverState() const;
    void setGameOverState(bool state);
    Piece getRandomPiece();
    u16 getLevel() const;
    Vector<Piece> getAllPieces() const;
    void drawGame() const;
    void drawScoreWord(const raylib::Font& font) const;
    void drawScore(const raylib::Font& font) const;
    void drawNext(const raylib::Font& font) const;
    void displayGameOver(const raylib::Font& font) const;
    void handleInput();
    void movePieceDown();
    // Debug
    Grid& getGrid();
};