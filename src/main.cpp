#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sierpinski_carpet.h"

#define UPDATE_TIME_INTERVAL 50 // timer interval in miliseconds

Carpet *carpet;
int mouseX = 0;
int mouseY = 0;
float windowWidth = 1.0f;
float windowHeight = 1.0f;


void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    carpet = new Carpet(1, 4);
}


void display()
{
    printf("mouseX:%i\tmouseY%i\n", mouseX, mouseY);
    
    float xwobble = ((float)mouseX)/windowWidth;
    float ywobble = ((float)mouseY)/windowHeight;
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xwobble, ywobble, 1.5f,
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
    
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
}

void update(int val)
{
    glutTimerFunc(UPDATE_TIME_INTERVAL, update, 0);
}

// mouse movement handler
void mousePosition(int x, int y) {
    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
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

    // capture mouse movement when mouse button down or up
    glutMotionFunc(mousePosition);
    glutPassiveMotionFunc(mousePosition);


    init();
    glutTimerFunc(UPDATE_TIME_INTERVAL, update, 0);
    glutMainLoop();
    return 0;
}
