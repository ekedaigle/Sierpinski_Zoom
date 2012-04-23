#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include "sierpinski_carpet.h"


#define UPDATE_TIME_INTERVAL 50 // timer interval in miliseconds
#define ZOOM_POINT_X 0.25
#define ZOOM_POINT_Y -0.25
#define ZOOM_POINT_Z 0.26

Carpet *carpet;
double xpos = 0, ypos = -0, zpos = 1.5;
double zoom = 0.1;

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 10.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -1.0, -1.0, 2.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
    
    carpet = new Carpet(4);
}


void display()
{

    glLoadIdentity();
    gluLookAt(xpos, ypos, zpos,
        xpos, ypos, zpos - 1,
        0.0f, 1.0f, 0.0f);

    glTranslatef(-zoom / 2.0 + 0.3, -zoom / 2.0 + 0.3, -zoom / 2.0);
    carpet->draw(zoom);
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
    gluPerspective(45, ratio, 0.01, 1000);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 2.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

}

void update(int val)
{
    zoom *= 1.01;

    if (zoom > 3)
        zoom /= 3;
    glutPostRedisplay();
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
