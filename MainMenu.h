#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <GL/glut.h>
#include <string>
#include <vector>

// Shared game state enum used across modules
enum GameState
{
    STATE_MAIN_MENU,
    STATE_TIC_TAC_TOE,
    STATE_EXIT // Added for Exit button functionality
};

// Difficulty levels
enum Difficulty
{
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD
};

// Button structure for menu UI
struct Button
{
    float x, y, width, height;
    std::string label;
    GameState targetState;
    bool hovered;

    Button(float x, float y, float width, float height,
           const std::string &label, GameState target)
        : x(x), y(y), width(width), height(height),
          label(label), targetState(target), hovered(false) {}
};

// Star particle for background animation
struct Star
{
    float x, y;
    float speed;
    float size;
};

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

    void init();
    void render();
    void update();

    GameState handleMouseClick(int button, int state, int x, int y);
    void handleMouseMove(int x, int y);
    void handleKeyPress(unsigned char key);
    void handleSpecialKeys(int key);

    Difficulty getSelectedDifficulty() const;

private:
    // Menu screens
    enum Screen
    {
        SCREEN_INITIAL, // Added for initial screen
        SCREEN_MAIN,
        SCREEN_DIFFICULTY,
        SCREEN_CONTROLS
    };

    // UI elements and state
    Screen currentScreen;
    std::vector<Button> initialButtons; // Added for initial screen buttons
    std::vector<Button> mainButtons;
    std::vector<Button> difficultyButtons;
    std::vector<Button> controlsButtons;
    std::vector<Star> stars;
    Difficulty selectedDifficulty;

    // UI helper functions
    void drawBackground();
    void drawButton(const Button &btn);
    void renderText(float x, float y, void *font, const std::string &text, bool center = false);
    void renderColoredText(float x, float y, void *font, const std::string &text, float r, float g, float b, bool center, bool underline); // Added for colored difficulty display

    // Star animation
    void initStars();
    void updateStars();
};

#endif // MAIN_MENU_H