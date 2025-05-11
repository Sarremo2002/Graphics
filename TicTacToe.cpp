#include "TicTacToe.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <GL/glut.h>

using namespace std;

// Constants for grid drawing
const float GRID_SIZE = 360.0f;
const float GRID_OFFSET_X = 140.0f;
const float GRID_OFFSET_Y = 60.0f;

TicTacToe::TicTacToe()
    : gridSize(3),
      isPlayerXTurn(true),
      result(RESULT_NONE),
      showingResultScreen(false),
      backButton(20, 20, 100, 40, "Back"),
      resetButton(520, 20, 100, 40, "Reset")
{
    resetGame();
}

TicTacToe::~TicTacToe()
{
    // Clean up resources if needed
}

void TicTacToe::init(Difficulty difficulty)
{
    // Set grid size based on difficulty
    switch (difficulty)
    {
    case DIFFICULTY_EASY:
        gridSize = 3; // 3x3
        break;
    case DIFFICULTY_MEDIUM:
        gridSize = 4; // 4x4
        break;
    case DIFFICULTY_HARD:
        gridSize = 5; // 5x5
        break;
    default:
        gridSize = 3;
        break;
    }

    resetGame();
}

void TicTacToe::resetGame()
{
    // Initialize the grid with empty cells
    grid.clear();
    grid.resize(gridSize, vector<CellState>(gridSize, CELL_EMPTY));

    // Reset game state
    isPlayerXTurn = true;
    result = RESULT_NONE;
    showingResultScreen = false;
}

void TicTacToe::update()
{
    // No animation updates needed
}

void TicTacToe::render()
{
    if (showingResultScreen)
    {
        drawResultScreen();
        return;
    }

    drawBackground();
    drawGrid();

    // Draw buttons
    drawButton(backButton);
    drawButton(resetButton);

    // Draw current player's turn
    glColor3f(1.0f, 1.0f, 1.0f);
    string turnText = isPlayerXTurn ? "Player X's Turn" : "Player O's Turn";
    renderText(320, 450, GLUT_BITMAP_HELVETICA_18, turnText, true);

    // Draw ESC key hint
    glColor3f(0.7f, 0.7f, 0.7f);
    renderText(320, 20, GLUT_BITMAP_HELVETICA_10, "Press ESC to return to main menu", true);
}

void TicTacToe::drawBackground()
{
    // Draw a gradient background
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.15f); // Dark blue at the top
    glVertex2f(0, 480);
    glVertex2f(640, 480);
    glColor3f(0.1f, 0.1f, 0.2f); // Slightly lighter blue at the bottom
    glVertex2f(640, 0);
    glVertex2f(0, 0);
    glEnd();

    // Draw a subtle grid pattern in the background
    glColor4f(0.2f, 0.2f, 0.3f, 0.2f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 20; i++)
    {
        // Horizontal lines
        glVertex2f(0, i * 24);
        glVertex2f(640, i * 24);

        // Vertical lines
        glVertex2f(i * 32, 0);
        glVertex2f(i * 32, 480);
    }
    glEnd();
    glLineWidth(1.0f);
}

void TicTacToe::drawGrid()
{
    // Calculate cell size based on grid size
    float cellSize = GRID_SIZE / gridSize;

    // Draw the grid lines
    glColor3f(0.7f, 0.7f, 0.8f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    for (int i = 0; i <= gridSize; i++)
    {
        // Horizontal lines
        float y = GRID_OFFSET_Y + i * cellSize;
        glVertex2f(GRID_OFFSET_X, y);
        glVertex2f(GRID_OFFSET_X + GRID_SIZE, y);

        // Vertical lines
        float x = GRID_OFFSET_X + i * cellSize;
        glVertex2f(x, GRID_OFFSET_Y);
        glVertex2f(x, GRID_OFFSET_Y + GRID_SIZE);
    }
    glEnd();
    glLineWidth(1.0f);

    // Draw cell contents
    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
        {
            drawCell(row, col);
        }
    }
}

void TicTacToe::drawCell(int row, int col)
{
    // Calculate cell size and position
    float cellSize = GRID_SIZE / gridSize;
    float cellX = GRID_OFFSET_X + col * cellSize;
    float cellY = GRID_OFFSET_Y + row * cellSize;

    // Center of the cell
    float centerX = cellX + cellSize * 0.5f;
    float centerY = cellY + cellSize * 0.5f;

    // Size of X or O (slightly smaller than cell)
    float symbolSize = cellSize * 0.7f;

    // Draw the cell content based on its state
    switch (grid[row][col])
    {
    case CELL_X:
        drawX(centerX, centerY, symbolSize);
        break;
    case CELL_O:
        drawO(centerX, centerY, symbolSize);
        break;
    case CELL_EMPTY:
        // Highlight cell on hover
        if (!showingResultScreen &&
            mouseX >= cellX && mouseX < cellX + cellSize &&
            mouseY >= cellY && mouseY < cellY + cellSize)
        {
            // Draw a semi-transparent symbol for the current player
            glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
            if (isPlayerXTurn)
                drawX(centerX, centerY, symbolSize * 0.8f);
            else
                drawO(centerX, centerY, symbolSize * 0.8f);
        }
        break;
    }
}

void TicTacToe::drawX(float centerX, float centerY, float size)
{
    // Draw an X with nice thick lines
    glLineWidth(5.0f);
    glColor3f(0.9f, 0.3f, 0.3f); // Reddish color for X

    float halfSize = size * 0.5f;

    glBegin(GL_LINES);
    // First diagonal line (top-left to bottom-right)
    glVertex2f(centerX - halfSize, centerY - halfSize);
    glVertex2f(centerX + halfSize, centerY + halfSize);

    // Second diagonal line (top-right to bottom-left)
    glVertex2f(centerX + halfSize, centerY - halfSize);
    glVertex2f(centerX - halfSize, centerY + halfSize);
    glEnd();

    glLineWidth(1.0f);
}

void TicTacToe::drawO(float centerX, float centerY, float size)
{
    // Draw an O with a nice thick circle
    glLineWidth(5.0f);
    glColor3f(0.3f, 0.7f, 0.9f); // Bluish color for O

    // Draw a circle for O
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 36; i++)
    {
        float angle = i * 10 * M_PI / 180.0f;
        float x = centerX + (size * 0.5f) * cos(angle);
        float y = centerY + (size * 0.5f) * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(1.0f);
}

void TicTacToe::drawResultScreen()
{
    // Draw a dark semi-transparent overlay
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(640, 0);
    glVertex2f(640, 480);
    glVertex2f(0, 480);
    glEnd();

    // Draw result message
    string resultText;
    switch (result)
    {
    case RESULT_X_WINS:
        glColor3f(0.9f, 0.3f, 0.3f); // Static reddish color
        resultText = "Player X Wins!";
        break;
    case RESULT_O_WINS:
        glColor3f(0.3f, 0.7f, 0.9f); // Static bluish color
        resultText = "Player O Wins!";
        break;
    case RESULT_DRAW:
        glColor3f(0.8f, 0.8f, 0.3f); // Static yellowish color
        resultText = "It's a Draw!";
        break;
    default:
        glColor3f(1.0f, 1.0f, 1.0f); // Static white
        resultText = "Game Over";
    }

    // Draw result text without scaling
    renderText(320, 240, GLUT_BITMAP_TIMES_ROMAN_24, resultText, true);

    // Draw "Press any key to continue" message
    glColor3f(0.8f, 0.8f, 0.8f);
    renderText(320, 180, GLUT_BITMAP_HELVETICA_12, "Click anywhere to play again", true);

    // Draw ESC key hint
    glColor3f(0.7f, 0.7f, 0.7f);
    renderText(320, 150, GLUT_BITMAP_HELVETICA_10, "Press ESC to return to main menu", true);

    // Draw Back button
    drawButton(backButton);
}

void TicTacToe::drawButton(const TicTacToeButton &btn)
{
    // Draw button shadow
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(btn.x + 3, btn.y - 3);
    glVertex2f(btn.x + btn.width + 3, btn.y - 3);
    glVertex2f(btn.x + btn.width + 3, btn.y + btn.height - 3);
    glVertex2f(btn.x + 3, btn.y + btn.height - 3);
    glEnd();

    // Draw button
    if (btn.hovered)
        glColor3f(0.3f, 0.5f, 0.9f); // PlayStation blue highlight
    else
        glColor3f(0.2f, 0.4f, 0.8f); // PlayStation blue

    glBegin(GL_QUADS);
    glVertex2f(btn.x, btn.y);
    glVertex2f(btn.x + btn.width, btn.y);
    glVertex2f(btn.x + btn.width, btn.y + btn.height);
    glVertex2f(btn.x, btn.y + btn.height);
    glEnd();

    // Draw button border
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(btn.x, btn.y);
    glVertex2f(btn.x + btn.width, btn.y);
    glVertex2f(btn.x + btn.width, btn.y + btn.height);
    glVertex2f(btn.x, btn.y + btn.height);
    glEnd();

    // Draw button text
    glColor3f(1.0f, 1.0f, 1.0f);
    renderText(btn.x + (btn.width / 2), btn.y + (btn.height / 2) + 5, GLUT_BITMAP_HELVETICA_12, btn.label, true);
}

void TicTacToe::renderText(float x, float y, void *font, const std::string &text, bool center)
{
    float offset = 0;
    if (center)
    {
        offset = 0.5f * glutBitmapLength(font, reinterpret_cast<const unsigned char *>(text.c_str()));
    }

    glRasterPos2f(x - offset, y);
    for (const char &c : text)
    {
        glutBitmapCharacter(font, c);
    }
}

GameState TicTacToe::handleMouseClick(int button, int state, int x, int y)
{
    // Store mouse position for hover effects
    mouseX = x;
    mouseY = y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Check if back button was clicked
        if (x >= backButton.x && x <= backButton.x + backButton.width &&
            y >= backButton.y && y <= backButton.y + backButton.height)
        {
            return STATE_MAIN_MENU;
        }

        // Check if reset button was clicked
        if (!showingResultScreen &&
            x >= resetButton.x && x <= resetButton.x + resetButton.width &&
            y >= resetButton.y && y <= resetButton.y + resetButton.height)
        {
            resetGame();
            return STATE_TIC_TAC_TOE;
        }

        // If showing result screen, any click resets the game
        if (showingResultScreen)
        {
            resetGame();
            return STATE_TIC_TAC_TOE;
        }

        // Convert screen coordinates to grid coordinates
        auto [row, col] = getGridCoordinates(x, y);

        // Make a move if valid
        if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
        {
            if (makeMove(row, col))
            {
                // Check for winner after the move
                result = checkWinner();
                if (result != RESULT_NONE)
                {
                    showingResultScreen = true;
                }
            }
        }
    }

    return STATE_TIC_TAC_TOE;
}

void TicTacToe::handleMouseMove(int x, int y)
{
    // Store mouse position for hover effects
    mouseX = x;
    mouseY = y;

    // Update button hover states
    backButton.hovered = (x >= backButton.x && x <= backButton.x + backButton.width &&
                          y >= backButton.y && y <= backButton.y + backButton.height);

    resetButton.hovered = (x >= resetButton.x && x <= resetButton.x + resetButton.width &&
                           y >= resetButton.y && y <= resetButton.y + resetButton.height);
}

GameState TicTacToe::handleKeyPress(unsigned char key)
{
    // Handle ESC key to return to main menu
    if (key == 27) // ASCII for ESC key
    {
        return STATE_MAIN_MENU;
    }

    if (showingResultScreen && (key == ' ' || key == 13)) // Space or Enter
    {
        resetGame();
    }

    return STATE_TIC_TAC_TOE;
}

void TicTacToe::handleSpecialKeys(int key)
{
    // Not implemented yet
}

bool TicTacToe::makeMove(int row, int col)
{
    // Check if move is valid
    if (!isValidMove(row, col))
    {
        return false;
    }

    // Make the move
    grid[row][col] = isPlayerXTurn ? CELL_X : CELL_O;

    // Switch turns
    isPlayerXTurn = !isPlayerXTurn;

    return true;
}

bool TicTacToe::isValidMove(int row, int col)
{
    // Check if coordinates are within grid bounds
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize)
    {
        return false;
    }

    // Check if cell is empty
    return grid[row][col] == CELL_EMPTY;
}

GameResult TicTacToe::checkWinner()
{
    // Check rows
    for (int row = 0; row < gridSize; row++)
    {
        if (grid[row][0] != CELL_EMPTY)
        {
            bool allSame = true;
            for (int col = 1; col < gridSize; col++)
            {
                if (grid[row][col] != grid[row][0])
                {
                    allSame = false;
                    break;
                }
            }
            if (allSame)
            {
                return (grid[row][0] == CELL_X) ? RESULT_X_WINS : RESULT_O_WINS;
            }
        }
    }

    // Check columns
    for (int col = 0; col < gridSize; col++)
    {
        if (grid[0][col] != CELL_EMPTY)
        {
            bool allSame = true;
            for (int row = 1; row < gridSize; row++)
            {
                if (grid[row][col] != grid[0][col])
                {
                    allSame = false;
                    break;
                }
            }
            if (allSame)
            {
                return (grid[0][col] == CELL_X) ? RESULT_X_WINS : RESULT_O_WINS;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    if (grid[0][0] != CELL_EMPTY)
    {
        bool allSame = true;
        for (int i = 1; i < gridSize; i++)
        {
            if (grid[i][i] != grid[0][0])
            {
                allSame = false;
                break;
            }
        }
        if (allSame)
        {
            return (grid[0][0] == CELL_X) ? RESULT_X_WINS : RESULT_O_WINS;
        }
    }

    // Check diagonal (top-right to bottom-left)
    if (grid[0][gridSize - 1] != CELL_EMPTY)
    {
        bool allSame = true;
        for (int i = 1; i < gridSize; i++)
        {
            if (grid[i][gridSize - 1 - i] != grid[0][gridSize - 1])
            {
                allSame = false;
                break;
            }
        }
        if (allSame)
        {
            return (grid[0][gridSize - 1] == CELL_X) ? RESULT_X_WINS : RESULT_O_WINS;
        }
    }

    // Check for draw (all cells filled)
    bool isDraw = true;
    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
        {
            if (grid[row][col] == CELL_EMPTY)
            {
                isDraw = false;
                break;
            }
        }
        if (!isDraw)
            break;
    }

    if (isDraw)
    {
        return RESULT_DRAW;
    }

    // No winner yet
    return RESULT_NONE;
}

std::pair<int, int> TicTacToe::getGridCoordinates(int x, int y)
{
    // Convert screen coordinates to grid coordinates
    float cellSize = GRID_SIZE / gridSize;

    int col = static_cast<int>((x - GRID_OFFSET_X) / cellSize);
    int row = static_cast<int>((y - GRID_OFFSET_Y) / cellSize);

    // Check bounds
    if (col < 0 || col >= gridSize || row < 0 || row >= gridSize)
    {
        return {-1, -1};
    }

    return {row, col};
}