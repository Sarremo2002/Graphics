#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <GL/glut.h>
#include <string>
#include <vector>

enum GameState
{
    STATE_MAIN_MENU,
    STATE_TIC_TAC_TOE,
    STATE_EXIT
};

enum Difficulty
{
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD
};

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
    enum Screen
    {
        SCREEN_INITIAL,
        SCREEN_MAIN,
        SCREEN_DIFFICULTY,
        SCREEN_CONTROLS
    };

    Screen currentScreen;
    std::vector<Button> initialButtons;
    std::vector<Button> mainButtons;
    std::vector<Button> difficultyButtons;
    std::vector<Button> controlsButtons;
    std::vector<Star> stars;
    Difficulty selectedDifficulty;

    void drawBackground();
    void drawButton(const Button &btn);
    void renderText(float x, float y, void *font, const std::string &text, bool center = false);
    void renderColoredText(float x, float y, void *font, const std::string &text, float r, float g, float b, bool center, bool underline); // Added for colored difficulty display

    void initStars();
    void updateStars();
};

#endif