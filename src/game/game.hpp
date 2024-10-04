#pragma once

#include <random>

#include "assets.hpp"
#include "colours.hpp"
#include "grid.hpp"
#include "tetromino.hpp"

extern bool debug;

enum class InputKeys {
    Left, Right, Down, Slam, Clockwise, Counterclockwise, Hold, Pause, Null
};

const raylib::Rectangle SCORE_RECTANGLE = raylib::Rectangle(320, 55, 170, 60);
const raylib::Rectangle NEXT_RECTANGLE = raylib::Rectangle(320, 215, 170, 180);

bool eventTriggered(f64 interval, f64& lastUpdateTime, const raylib::Window& window);

class Game {
  private:
    Grid g;
    bool gameOver = false;
    std::vector<Piece> pieces;
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
    std::vector<Piece> getAllPieces() const;
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