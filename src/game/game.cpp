#include "../../include/game/game.hpp"

namespace Utility {
    bool eventTriggered(f64 interval, f64& lastUpdateTime, const raylib::Window& window) {
        #ifdef DEBUG
        assert(interval >= 0);
        assert(lastUpdateTime >= 0);
        #endif
        f64 currentTime = window.GetTime();
        if (currentTime - lastUpdateTime >= interval) {
            lastUpdateTime = currentTime;
            return true;
        }
        return false;
    }
}

Game::Game():
    g{Grid()}, pieces{getAllPieces()}, gen{std::random_device{}()},
    currentPiece{getRandomPiece()}, nextPiece{getRandomPiece()},
    clearSound{LoadSound("assets/sounds/clear.mp3")},
    rotateSound{LoadSound("assets/sounds/rotate.mp3")},
    music{LoadMusicStream("assets/sounds/music.mp3")} {
    if (debug)
        std::println(debugLogger, "Constructing game.");
    InitAudioDevice();
    PlayMusicStream(music);
}


Game::~Game() {
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}

bool Game::getGameOverState() const {
    return gameOver;
}

void Game::setGameOverState(bool state) {
    gameOver = state;
}

void Game::resetGame() {
    if (debug)
        std::println(debugLogger, "Game resetting.");
    g.reinitialiseGrid();
    pieces = getAllPieces();
    currentPiece = getRandomPiece();
    nextPiece = getRandomPiece();
    score = 0;
}

bool Game::isPieceOutside() const {
    std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS> tiles = currentPiece.getCellPositions();
    for (const Position& tile: tiles) 
        if (g.isCellOutside(tile.getRow(), tile.getColumn()))
            return true;
    return false;
}

Piece Game::getRandomPiece() {
    if (pieces.empty()) 
        pieces = getAllPieces();
    std::uniform_int_distribution<> dis(0, pieces.size() - 1);
    usize randomIndex = dis(gen);
    if (debug)
        std::println(debugLogger, "Index generated: {}, of pieces size: ", pieces.size());
    #ifdef DEBUG
    Piece p = pieces.at(randomIndex);
    #else
    Piece p = pieces[randomIndex];
    #endif
    pieces.erase(pieces.begin() + randomIndex);
    return p;
}

u16 Game::getLevel() const {
    return level;
}

std::vector<Piece> Game::getAllPieces() const {
    return {IPiece(), JPiece(), LPiece(), OPiece(), SPiece(), TPiece(), ZPiece()};
}

void Game::drawGame() const {
    g.drawGrid();
    currentPiece.drawPiece(GameInfo::GRID_OFFSET + 1, GameInfo::GRID_OFFSET + 1);
    switch (nextPiece.getID()) {
        case PieceID::ID_L_PIECE:
            nextPiece.drawPiece(255, 290);
            break;
        case PieceID::ID_O_PIECE:
            nextPiece.drawPiece(255, 280);
            break;
        default:
            nextPiece.drawPiece(270, 270);
    }
}

void Game::drawScoreWord(const raylib::Font& font) const {
    raylib::DrawTextEx(font, const_cast<char*>("Score"), {365, 15}, 38, 2, WHITE);
    GameRectangles::SCORE_RECTANGLE.DrawRounded(0.3, 6, Colours::ROYAL_BLUE);
}

void Game::drawScore(const raylib::Font& font) const {
    char scoreText[10];
    sprintf(scoreText, "%d", score);
    raylib::Vector2 textSize = font.MeasureText(scoreText, 38, 2);
    raylib::DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
}

void Game::drawNext(const raylib::Font& font) const {
    raylib::DrawTextEx(font, const_cast<char*>("Next"), {370, 175}, 38, 2, WHITE);
    GameRectangles::NEXT_RECTANGLE.DrawRounded(0.3, 6, Colours::ROYAL_BLUE);
}

void Game::displayGameOver(const raylib::Font& font) const {
    raylib::DrawTextEx(font, const_cast<char*>("GAME OVER"), {320, 450}, 38, 2, WHITE);
}

void Game::movePieceLeft() {
    if (!getGameOverState()) {
        if (debug)
            std::println(debugLogger, "Attempting to move piece left.");
        currentPiece.movePiece(0, -1);
        if (isPieceOutside() || !pieceFits()) {
            if (debug)
                std::println(debugLogger, "FAILED to move piece left!");
            currentPiece.movePiece(0, 1);
        }
    }
}

void Game::movePieceRight() {
    if (!getGameOverState()) {
        if (debug)
            std::println(debugLogger, "Attempting to move piece right.");
        currentPiece.movePiece(0, 1);
        if (isPieceOutside() || !pieceFits()) {
            if (debug)
                std::println(debugLogger, "FAILED to move piece right!");
            currentPiece.movePiece(0, -1);
        }
    }
}

void Game::lockPiece() {
    if (debug)
        std::println(debugLogger, "Locking piece.");
    std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS> tiles = currentPiece.getCellPositions();
    for (const Position& tile: tiles)
        g.setCell(tile.getRow(), tile.getColumn(), currentPiece.getID());
    currentPiece = nextPiece;
    if (!pieceFits()) {
        if (debug)
            std::println(debugLogger, "Game over!\nEnding game.");
        setGameOverState(true);
    }
    nextPiece = getRandomPiece();
    u8 rowsCleared = g.clearFullRows();
    if (rowsCleared != 0) {
        PlaySound(clearSound);
        updateScore(rowsCleared, 0);
    }
}

bool Game::pieceFits() const {
    std::array<Position, GameInfo::NUM_TETROMINO_BLOCKS> tiles = currentPiece.getCellPositions();
    for (const Position& tile: tiles)
        if (!g.isCellEmpty(tile.getRow(), tile.getColumn()))
            return false;
    return true;
}

void Game::movePieceDown() {
    if (!getGameOverState()) {
        currentPiece.movePiece(1, 0);
        if (isPieceOutside() || !pieceFits()) {
            currentPiece.movePiece(-1, 0);
            lockPiece();
        }
    }
}

void Game::slamPiece() {
    if (!getGameOverState()) {
        if (debug)
            std::println(debugLogger, "Attempting to slam piece.");
        while (true) {
            currentPiece.movePiece(1, 0);
            if (isPieceOutside() || !pieceFits()) {
                currentPiece.movePiece(-1, 0);
                lockPiece();
                break;
            }
        }
    }
}

void Game::rotatePieceClockwise() {
    if (!getGameOverState()) {
        if (debug)
            std::println(debugLogger, "Attempting to rotate piece clockwise.");
        currentPiece.rotatePieceClockwise();
        if (isPieceOutside() || !pieceFits()) {
            if (debug)
                std::println(debugLogger, "FAILED to rotate piece clockwise!");
            currentPiece.rotatePieceCounterclockwise();
        } else 
            PlaySound(rotateSound);
    }
}

void Game::rotatePieceCounterclockwise() {
    if (!getGameOverState()) {
        if (debug)
            std::println(debugLogger, "Attempting to rotate piece counterclockwise.");
        currentPiece.rotatePieceCounterclockwise();
        if (isPieceOutside() || !pieceFits()) {
            if (debug)
                std::println(debugLogger, "FAILED to rotate piece counterclockwise!");
            currentPiece.rotatePieceClockwise();
        } else 
            PlaySound(rotateSound);
    }
}

void Game::updateScore(u8 linesCleared, u8 movedDown) {
    #ifdef DEBUG
    assert(linesCleared <= 4);
    assert(movedDown <= 20);
    #endif
    switch (linesCleared) {
        case 1:
            score += 100;
            break;
        case 2:
            score += 200;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 1000;
            break;
        default:
            break;
    }
    score += movedDown;
}

void Game::handleInput() {
    i32 keyPressed = raylib::Keyboard::GetKeyPressed();
    if (getGameOverState() && keyPressed != 0) {
        setGameOverState(false);
        resetGame();
    }
    InputKeys key;
    if (keyPressed == KeyboardKey::KEY_LEFT || keyPressed == KeyboardKey::KEY_KP_4) key = InputKeys::Left;
    else if (keyPressed == KeyboardKey::KEY_RIGHT || keyPressed == KeyboardKey::KEY_KP_6) key = InputKeys::Right;
    else if (keyPressed == KeyboardKey::KEY_DOWN || keyPressed == KeyboardKey::KEY_KP_2) key = InputKeys::Down;
    else if (keyPressed == KeyboardKey::KEY_SPACE || keyPressed == KeyboardKey::KEY_KP_8) key = InputKeys::Slam;
    else if (keyPressed == KeyboardKey::KEY_UP || keyPressed == KeyboardKey::KEY_X || keyPressed == KeyboardKey::KEY_KP_1 || keyPressed == KeyboardKey::KEY_KP_5 || keyPressed == KeyboardKey::KEY_KP_9) key = InputKeys::Clockwise;
    else if (keyPressed == KeyboardKey::KEY_LEFT_CONTROL || keyPressed == KeyboardKey::KEY_Z || keyPressed == KeyboardKey::KEY_KP_3 || keyPressed == KeyboardKey::KEY_KP_7) key = InputKeys::Counterclockwise;
    else if (keyPressed == KeyboardKey::KEY_LEFT_SHIFT || keyPressed == KeyboardKey::KEY_C || keyPressed == KeyboardKey::KEY_KP_0) key = InputKeys::Hold;
    else if (keyPressed == KeyboardKey::KEY_ESCAPE || keyPressed == KeyboardKey::KEY_F1) key = InputKeys::Pause;
    else key = InputKeys::Null;
    switch (key) {
        case InputKeys::Left:
            movePieceLeft();
            break;
        case InputKeys::Right:
            movePieceRight();
            break;
        case InputKeys::Down:
            movePieceDown();
            updateScore(0, 1);
            break;
        case InputKeys::Slam:
            slamPiece();
            updateScore(0, 20);
            break;
        case InputKeys::Clockwise:
            rotatePieceClockwise();
            break;
        case InputKeys::Counterclockwise:
            rotatePieceCounterclockwise();
            break;
        case InputKeys::Hold:
            break;
        case InputKeys::Pause:
            break;
        default:
            break;
    }
}

// Debug method
Grid& Game::getGrid() {
    return g;
}
