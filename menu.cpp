#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Screen { MAIN_MENU, DIFFICULTY_SCREEN };
Screen currentScreen = MAIN_MENU;
int gameWindow = 0;
struct Button {
    float x, y, width, height;
    string label;
    Screen targetScreen;
    bool hovered = false;
};

struct Star {
    float x, y;
    float speed;
};

Button buttons[7] = {
    {220, 260, 200, 60, "Start", MAIN_MENU},
    {220, 180, 200, 60, "Difficulty", DIFFICULTY_SCREEN},
    {220, 100, 200, 60, "Exit", MAIN_MENU},
    {20, 20, 100, 40, "Back", MAIN_MENU},
    {220, 300, 200, 60, "Easy", DIFFICULTY_SCREEN},
    {220, 220, 200, 60, "Medium", DIFFICULTY_SCREEN},
    {220, 140, 200, 60, "Hard", DIFFICULTY_SCREEN}
};

vector<Star> stars;
string selectedDifficulty = "None";

void initStars() {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        Star s;
        s.x = rand() % 640;
        s.y = rand() % 480;
        s.speed = 0.5f + (rand() % 100) / 100.0f;
        stars.push_back(s);
    }
}

void updateStars(int value) {
    for (int i = 0; i < stars.size(); i++) {
        stars[i].y -= stars[i].speed;
        if (stars[i].y < 0) {
            stars[i].y = 480;
            stars[i].x = rand() % 640;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, updateStars, 0);
}

void renderBitmapString(float x, float y, void* font, const char* string, bool center = false) {
    if (center) {
        x -= strlen(string) * 4.5f;
    }
    glRasterPos2f(x, y);
    for (int i = 0; string[i] != '\0'; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

void drawButton(Button btn, bool isBack = false) {
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(btn.x + 5, btn.y - 5);
    glVertex2f(btn.x + btn.width + 5, btn.y - 5);
    glVertex2f(btn.x + btn.width + 5, btn.y + btn.height - 5);
    glVertex2f(btn.x + 5, btn.y + btn.height - 5);
    glEnd();

    if (btn.hovered)
        glColor3f(0.3f, 0.7f, 0.9f);
    else
        glColor3f(0.2f, 0.6f, 0.8f);

    glBegin(GL_QUADS);
    glVertex2f(btn.x, btn.y);
    glVertex2f(btn.x + btn.width, btn.y);
    glVertex2f(btn.x + btn.width, btn.y + btn.height);
    glVertex2f(btn.x, btn.y + btn.height);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(btn.x, btn.y);
    glVertex2f(btn.x + btn.width, btn.y);
    glVertex2f(btn.x + btn.width, btn.y + btn.height);
    glVertex2f(btn.x, btn.y + btn.height);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(btn.x + (btn.width / 2), btn.y + (btn.height / 2) - 4, GLUT_BITMAP_HELVETICA_18, btn.label.c_str(), true);
}

void drawBackground() {
    glColor3f(0.0f, 0.0f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(640, 0);
    glVertex2f(640, 480);
    glVertex2f(0, 480);
    glEnd();

    glColor3f(1, 1, 1);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < stars.size(); i++) {
        glVertex2f(stars[i].x, stars[i].y);
    }
    glEnd();
}

void drawMainMenu() {
    drawBackground();

    glColor3f(1, 1, 1);
    renderBitmapString(300, 380, GLUT_BITMAP_TIMES_ROMAN_24, "Main Menu", true);

    for (int i = 0; i < 3; i++) {
        drawButton(buttons[i]);
    }

    renderBitmapString(320, 50, GLUT_BITMAP_HELVETICA_12, ("Selected Difficulty: " + selectedDifficulty).c_str(), true);
}

void drawDifficultyScreen() {
    drawBackground();
    renderBitmapString(330, 380, GLUT_BITMAP_TIMES_ROMAN_24, "Select Difficulty", true);

    for (int i = 4; i < 7; i++) {
        drawButton(buttons[i]);
    }

    drawButton(buttons[3], true); // Back button

    renderBitmapString(320, 80, GLUT_BITMAP_HELVETICA_12, ("Selected Difficulty: " + selectedDifficulty).c_str(), true);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScreen == MAIN_MENU) {
        drawMainMenu();
    }
    else {
        drawDifficultyScreen();
    }

    glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 480 - y;

        if (currentScreen == MAIN_MENU) {
            for (int i = 0; i < 3; i++) {
                if (x >= buttons[i].x && x <= buttons[i].x + buttons[i].width &&
                    y >= buttons[i].y && y <= buttons[i].y + buttons[i].height) {
                    if (buttons[i].label == "Exit") {
                        exit(0);
                    } else if (buttons[i].label == "Start") {
                        cout << "Start game clicked ()" << endl;

                    } else {
                        currentScreen = buttons[i].targetScreen;
                        glutPostRedisplay();
                    }
                }
            }
        } else {
            if (x >= buttons[3].x && x <= buttons[3].x + buttons[3].width &&
                y >= buttons[3].y && y <= buttons[3].y + buttons[3].height) {
                currentScreen = MAIN_MENU;
                glutPostRedisplay();
            }

            for (int i = 4; i < 7; i++) {
                if (x >= buttons[i].x && x <= buttons[i].x + buttons[i].width &&
                    y >= buttons[i].y && y <= buttons[i].y + buttons[i].height) {
                    selectedDifficulty = buttons[i].label;
                    cout << "Difficulty set to " << selectedDifficulty << endl;
                    glutPostRedisplay();
                }
            }
        }
    }
}

void passiveMotion(int x, int y) {
    y = 480 - y;

    if (currentScreen == MAIN_MENU) {
        for (int i = 0; i < 3; i++) {
            buttons[i].hovered = (x >= buttons[i].x && x <= buttons[i].x + buttons[i].width &&
                                  y >= buttons[i].y && y <= buttons[i].y + buttons[i].height);
        }
    } else {
        for (int i = 3; i < 7; i++) {
            buttons[i].hovered = (x >= buttons[i].x && x <= buttons[i].x + buttons[i].width &&
                                  y >= buttons[i].y && y <= buttons[i].y + buttons[i].height);
        }
    }

    glutPostRedisplay(); 
}

void gameDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(320, 240, GLUT_BITMAP_HELVETICA_18, "Game Started!", true);

    glutSwapBuffers();
}


void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    initStars();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Menu");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMotion);
    glutTimerFunc(0, updateStars, 0);

    glutMainLoop();
    return 0;
}
