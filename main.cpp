#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "MainMenu.h"
#include "TicTacToe.h"

using namespace std;

// Global variables for managing game state
MainMenu mainMenu;
TicTacToe ticTacToe;
GameState currentGameState = STATE_MAIN_MENU;

void display();
void mouse(int btn, int state, int x, int y);
void passiveMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void updateAnimation(int value);
void init();

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentGameState)
    {
    case STATE_MAIN_MENU:
        mainMenu.render();
        break;
    case STATE_TIC_TAC_TOE:
        ticTacToe.render();
        break;
    }

    glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
    y = 480 - y; // Convert to OpenGL coordinates

    switch (currentGameState)
    {
    case STATE_MAIN_MENU:
    {
        GameState nextState = mainMenu.handleMouseClick(btn, state, x, y);
        if (nextState == STATE_EXIT)
        {
            exit(0); // Exit the program
        }
        else if (nextState != STATE_MAIN_MENU)
        {
            currentGameState = nextState;
            if (currentGameState == STATE_TIC_TAC_TOE)
            {
                // Initialize the game with the selected difficulty
                ticTacToe.init(mainMenu.getSelectedDifficulty());
            }
        }
        break;
    }
    case STATE_TIC_TAC_TOE:
        if (ticTacToe.handleMouseClick(btn, state, x, y) == STATE_MAIN_MENU)
        {
            currentGameState = STATE_MAIN_MENU;
        }
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

// Mouse movement handler for hovering effects
void passiveMotion(int x, int y)
{
    y = 480 - y; // Convert to OpenGL coordinates

    switch (currentGameState)
    {
    case STATE_MAIN_MENU:
        mainMenu.handleMouseMove(x, y);
        break;
    case STATE_TIC_TAC_TOE:
        ticTacToe.handleMouseMove(x, y);
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

// Keyboard handler for keyboard navigation
void keyboard(unsigned char key, int x, int y)
{
    switch (currentGameState)
    {
    case STATE_MAIN_MENU:
        mainMenu.handleKeyPress(key);
        break;
    case STATE_TIC_TAC_TOE:
        if (ticTacToe.handleKeyPress(key) == STATE_MAIN_MENU)
        {
            currentGameState = STATE_MAIN_MENU;
        }
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

// Special key handler (arrow keys, etc.)
void specialKeys(int key, int x, int y)
{
    switch (currentGameState)
    {
    case STATE_MAIN_MENU:
        mainMenu.handleSpecialKeys(key);
        break;
    case STATE_TIC_TAC_TOE:
        ticTacToe.handleSpecialKeys(key);
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void updateAnimation(int value)
{
    switch (currentGameState)
    {
    case STATE_MAIN_MENU:
        mainMenu.update();
        break;
    case STATE_TIC_TAC_TOE:
        ticTacToe.update();
        break;
    default:
        break;
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateAnimation, 0); // ~60 FPS
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mainMenu.init();
}

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(0)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tic Tac Toe");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMotion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, updateAnimation, 0);

    init();

    glutMainLoop();

    return 0;
}