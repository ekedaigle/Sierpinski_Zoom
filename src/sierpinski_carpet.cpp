#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cmath>
#include "sierpinski_carpet.h"

Carpet::Carpet(double size, int levels) : size(size), levels(levels)
{
}

void Carpet::draw(double x, double y, double z, int level, double size)
{
    if (level == 0)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX);
        glutSolidCube(size);
        glPopMatrix();
        return;
    }

    double next_size = size / 3.0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;

            for (int k = -1; k <= 1; k++)
            {
                if ((i == 0 && k == 0) || (j == 0 && k == 0))
                    continue;

                draw(x + i * next_size, y + j * next_size, z + k * next_size, level - 1, next_size);
            }
        }
    }
}

void Carpet::draw()
{
    draw(0.0, 0.0, 0.0, 3, size);
}
