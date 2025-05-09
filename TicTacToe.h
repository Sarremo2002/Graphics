#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <GL/glut.h>
#include <vector>
#include <string>
#include "MainMenu.h"

// Cell states
enum CellState
{
    CELL_EMPTY,
    CELL_X,
    CELL_O
};

// Game result states
enum GameResult
{
    RESULT_NONE,
    RESULT_X_WINS,
    RESULT_O_WINS,
    RESULT_DRAW
};

// Button for UI
struct TicTacToeButton
{
    float x, y, width, height;
    std::string label;
    bool hovered;

    TicTacToeButton(float x, float y, float width, float height, const std::string &label)
        : x(x), y(y), width(width), height(height), label(label), hovered(false) {}
};

class TicTacToe
{
public:
    TicTacToe();
    ~TicTacToe();

    void init(Difficulty difficulty);
    void render();
    void update();

    GameState handleMouseClick(int button, int state, int x, int y);
    void handleMouseMove(int x, int y);
    GameState handleKeyPress(unsigned char key);
    void handleSpecialKeys(int key);

private:
    // Game state
    int gridSize;                             // Size of the grid (3x3, 4x4, or 5x5)
    std::vector<std::vector<CellState>> grid; // Game grid
    bool isPlayerXTurn;                       // True if it's X's turn, false if it's O's turn
    GameResult result;                        // Current game result
    float animationTimer;                     // Timer for animations
    bool showingResultScreen;                 // True if showing the result screen
    int mouseX, mouseY;                       // Current mouse position for hover effects

    // UI elements
    TicTacToeButton backButton;  // Back button to return to menu
    TicTacToeButton resetButton; // Reset button to restart the game

    // Rendering helpers
    void drawBackground();
    void drawGrid();
    void drawCell(int row, int col);
    void drawX(float centerX, float centerY, float size);
    void drawO(float centerX, float centerY, float size);
    void drawResultScreen();
    void drawButton(const TicTacToeButton &btn);
    void renderText(float x, float y, void *font, const std::string &text, bool center = false);

    // Game logic
    void resetGame();
    bool makeMove(int row, int col);
    GameResult checkWinner();
    std::pair<int, int> getGridCoordinates(int x, int y);
    bool isValidMove(int row, int col);
};

#endif