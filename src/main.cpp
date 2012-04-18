#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <time.h>
#include "sierpinski_carpet.h"

#define UPDATE_TIME_INTERVAL 50 // timer interval in miliseconds

Carpet *carpet;

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    carpet = new Carpet(0.5, 5);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 1.5f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    carpet->draw();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    double ratio = (double)width / (double)height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void update(int val)
{
    glutTimerFunc(UPDATE_TIME_INTERVAL, update, 0);
}

int main(int argc, char *argv[])
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski Zoom");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();
    glutTimerFunc(UPDATE_TIME_INTERVAL, update, 0);
    glutMainLoop();
    return 0;
}
