// CPPGems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GL/glew.h>
#include <string>
#include "windowClass.h"

Sn_GemContainer* container;

void resizeHandle(int width, int height)
{
    glutReshapeWindow(800, 800);
}

void mouseHandle(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        container->handleMouseClick(x, y);
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        container->handleRightMouseClick(x, y);
}

void idleHandle(void)
{
    container->idleFunc();
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            container->releaseBall();
            break;
        case GLUT_KEY_LEFT:
            container->moveLeft();
            break;
        case GLUT_KEY_RIGHT:
            container->moveRight();
            break;
    }
}


void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    auto score = container->calcScore();
    std::string str = "Score: " + std::to_string(score);
    glutSetWindowTitle(str.c_str());
    container->drawGems();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    int xSize = 800;
    int ySize = 800;
    int gemSizeX = 50;
    int gemSizeY = 10;
    container = new Sn_GemContainer(xSize, ySize, gemSizeX, gemSizeY);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(xSize, ySize);           
    glutInitWindowPosition(10, 10);   
    glutCreateWindow("Gems Game");

    glutSpecialFunc(specialKeys);
    glutDisplayFunc(displayMe);
    glutReshapeFunc(resizeHandle);
    glutMouseFunc(mouseHandle);
    glutIdleFunc(idleHandle);

    glutMainLoop();

    delete container;
    return 0;
}
