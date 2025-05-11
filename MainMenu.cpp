#include "MainMenu.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>

using namespace std;

MainMenu::MainMenu() : currentScreen(SCREEN_INITIAL), selectedDifficulty(DIFFICULTY_MEDIUM)
{
    // Initialize buttons will be done in init()
}

MainMenu::~MainMenu()
{
    // Clean up resources if needed
}

void MainMenu::init()
{
    // Initialize initial screen buttons
    initialButtons.clear();
    initialButtons.push_back(Button(220, 240, 200, 60, "Start", STATE_MAIN_MENU));
    initialButtons.push_back(Button(220, 160, 200, 60, "Exit", STATE_EXIT));

    // Initialize main menu buttons
    mainButtons.clear();
    mainButtons.push_back(Button(220, 320, 200, 60, "Tic Tac Toe", STATE_TIC_TAC_TOE));
    mainButtons.push_back(Button(220, 200, 200, 60, "Controls", STATE_MAIN_MENU));
    mainButtons.push_back(Button(220, 80, 200, 60, "Difficulty", STATE_MAIN_MENU));

    // Initialize difficulty selection buttons
    difficultyButtons.clear();
    difficultyButtons.push_back(Button(220, 300, 200, 60, "Easy", STATE_MAIN_MENU));
    difficultyButtons.push_back(Button(220, 220, 200, 60, "Medium", STATE_MAIN_MENU));
    difficultyButtons.push_back(Button(220, 140, 200, 60, "Hard", STATE_MAIN_MENU));
    difficultyButtons.push_back(Button(20, 20, 100, 40, "Back", STATE_MAIN_MENU));
    

    // Initialize star background
    initStars();
}

void MainMenu::initStars()
{
    stars.clear();
    for (int i = 0; i < 100; i++)
    {
        Star s;
        s.x = rand() % 640;
        s.y = rand() % 480;
        s.speed = 0.5f + (rand() % 100) / 100.0f;
        s.size = 1.0f + (rand() % 3) / 2.0f;
        stars.push_back(s);
    }
}

void MainMenu::updateStars()
{
    for (auto &star : stars)
    {
        star.y -= star.speed;
        if (star.y < 0)
        {
            star.y = 480;
            star.x = rand() % 640;
        }
    }
}

void MainMenu::update()
{
    updateStars();
}

void MainMenu::render()
{
    drawBackground();

    if (currentScreen == SCREEN_INITIAL)
    {
        // Draw initial screen buttons
        for (const auto &btn : initialButtons)
        {
            drawButton(btn);
        }
    }
    else if (currentScreen == SCREEN_MAIN)
    {
        // Draw main menu buttons
        for (const auto &btn : mainButtons)
        {
            drawButton(btn);
        }

        // Show current difficulty with color and underline
        string difficultyText = "Current Difficulty: ";
        float r, g, b;
        switch (selectedDifficulty)
        {
        case DIFFICULTY_EASY:
            difficultyText += "Easy";
            r = 0.0f;
            g = 1.0f;
            b = 0.0f; // Green
            break;
        case DIFFICULTY_MEDIUM:
            difficultyText += "Medium";
            r = 1.0f;
            g = 0.5f;
            b = 0.0f; // Orange
            break;
        case DIFFICULTY_HARD:
            difficultyText += "Hard";
            r = 1.0f;
            g = 0.0f;
            b = 0.0f; // Red
            break;
        }
        renderColoredText(320, 30, GLUT_BITMAP_HELVETICA_12, difficultyText, r, g, b, true, true);
    }
    else if (currentScreen == SCREEN_DIFFICULTY)
    {
        // Draw title
        glColor3f(1.0f, 1.0f, 1.0f);
        renderText(320, 400, GLUT_BITMAP_TIMES_ROMAN_24, "Select Difficulty", true);

        // Draw difficulty buttons
        for (const auto &btn : difficultyButtons)
        {
            drawButton(btn);
        }

        // Show current difficulty with color and underline
        string difficultyText = "Current Difficulty: ";
        float r, g, b;
        switch (selectedDifficulty)
        {
        case DIFFICULTY_EASY:
            difficultyText += "Easy";
            r = 0.0f;
            g = 1.0f;
            b = 0.0f; // Green
            break;
        case DIFFICULTY_MEDIUM:
            difficultyText += "Medium";
            r = 1.0f;
            g = 0.5f;
            b = 0.0f; // Orange
            break;
        case DIFFICULTY_HARD:
            difficultyText += "Hard";
            r = 1.0f;
            g = 0.0f;
            b = 0.0f; // Red
            break;
        }
        renderColoredText(320, 80, GLUT_BITMAP_HELVETICA_12, difficultyText, r, g, b, true, true);
    }
    else if (currentScreen == SCREEN_CONTROLS)
    {
  
    glColor3f(1.0f, 1.0f, 1.0f);
    renderText(320, 400, GLUT_BITMAP_TIMES_ROMAN_24, "Controls", true);

    
    renderText(320, 320, GLUT_BITMAP_HELVETICA_12, "Use the mouse to click on menu buttons.", true);
    renderText(320, 290, GLUT_BITMAP_HELVETICA_12, "In-game controls will vary by game mode.", true);
    renderText(320, 260, GLUT_BITMAP_HELVETICA_12, "Press ESC to return to previous screen .", true);

    
    for (const auto &btn : controlsButtons)
    {
        drawButton(btn);
    }
    }
}

void MainMenu::drawBackground()
{
    // Draw space background
    glColor3f(0.0f, 0.0f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(640, 0);
    glVertex2f(640, 480);
    glVertex2f(0, 480);
    glEnd();

    // Draw stars with different sizes
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (const auto &star : stars)
    {
        float brightness = 0.7f + (rand() % 30) / 100.0f;
        glColor3f(brightness, brightness, brightness);
        glPointSize(star.size);
        glVertex2f(star.x, star.y);
    }
    glEnd();

    // Reset point size
    glPointSize(1.0f);
}

void MainMenu::drawButton(const Button &btn)
{
    // Draw button shadow
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(btn.x + 5, btn.y - 5);
    glVertex2f(btn.x + btn.width + 5, btn.y - 5);
    glVertex2f(btn.x + btn.width + 5, btn.y + btn.height - 5);
    glVertex2f(btn.x + 5, btn.y + btn.height - 5);
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

void MainMenu::renderText(float x, float y, void *font, const std::string &text, bool center)
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

void MainMenu::renderColoredText(float x, float y, void *font, const std::string &text, float r, float g, float b, bool center, bool underline)
{
    glColor3f(r, g, b);
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
    if (underline)
    {
        float startX = x - offset;
        float endX = x + offset;
        glBegin(GL_LINES);
        glVertex2f(startX, y - 2);
        glVertex2f(endX, y - 2);
        glEnd();
    }
}

GameState MainMenu::handleMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (currentScreen == SCREEN_INITIAL)
        {
            for (const auto &btn : initialButtons)
            {
                if (x >= btn.x && x <= btn.x + btn.width &&
                    y >= btn.y && y <= btn.y + btn.height)
                {
                    if (btn.label == "Start")
                    {
                        currentScreen = SCREEN_MAIN;
                    }
                    return btn.targetState;
                }
            }
        }
        else if (currentScreen == SCREEN_MAIN)
        {
            for (const auto &btn : mainButtons)
            {
                if (x >= btn.x && x <= btn.x + btn.width &&
                    y >= btn.y && y <= btn.y + btn.height)
                {
                    if (btn.label == "Difficulty")
                    {
                        currentScreen = SCREEN_DIFFICULTY;
                        return STATE_MAIN_MENU;
                    }
                    else
                    {
                        return btn.targetState;
                    }
                }
            }
        }
        else if (currentScreen == SCREEN_DIFFICULTY)
        {
            for (const auto &btn : difficultyButtons)
            {
                if (x >= btn.x && x <= btn.x + btn.width &&
                    y >= btn.y && y <= btn.y + btn.height)
                {
                    if (btn.label == "Back")
                    {
                        currentScreen = SCREEN_INITIAL; // Already updated in previous request
                    }
                    else if (btn.label == "Easy")
                    {
                        selectedDifficulty = DIFFICULTY_EASY;
                        currentScreen = SCREEN_MAIN;
                    }
                    else if (btn.label == "Medium")
                    {
                        selectedDifficulty = DIFFICULTY_MEDIUM;
                        currentScreen = SCREEN_MAIN;
                    }
                    else if (btn.label == "Hard")
                    {
                        selectedDifficulty = DIFFICULTY_HARD;
                        currentScreen = SCREEN_MAIN;
                    }
                    return STATE_MAIN_MENU;
                }
            }
        }

        else if (currentScreen == SCREEN_CONTROLS)
{
    for (const auto &btn : controlsButtons)
    {
        if (x >= btn.x && x <= btn.x + btn.width &&
            y >= btn.y && y <= btn.y + btn.height)
        {
            if (btn.label == "Back")
            {
                currentScreen = SCREEN_MAIN;
            }
            return STATE_MAIN_MENU;
        }
    }
}


    }
    return STATE_MAIN_MENU;
}

void MainMenu::handleMouseMove(int x, int y)
{
    if (currentScreen == SCREEN_INITIAL)
    {
        for (auto &btn : initialButtons)
        {
            btn.hovered = (x >= btn.x && x <= btn.x + btn.width &&
                           y >= btn.y && y <= btn.y + btn.height);
        }
    }
    else if (currentScreen == SCREEN_MAIN)
    {
        for (auto &btn : mainButtons)
        {
            btn.hovered = (x >= btn.x && x <= btn.x + btn.width &&
                           y >= btn.y && y <= btn.y + btn.height);
        }
    }
    else if (currentScreen == SCREEN_DIFFICULTY)
    {
        for (auto &btn : difficultyButtons)
        {
            btn.hovered = (x >= btn.x && x <= btn.x + btn.width &&
                           y >= btn.y && y <= btn.y + btn.height);
        }
    }
}

void MainMenu::handleKeyPress(unsigned char key)
{
    if (key == 27) // Escape key
    {
        if (currentScreen == SCREEN_MAIN )
        {
            currentScreen = SCREEN_MAIN;
        }
    }


    

    
}

void MainMenu::handleSpecialKeys(int key)
{
    // Not implemented yet
}

Difficulty MainMenu::getSelectedDifficulty() const
{
    return selectedDifficulty;
}