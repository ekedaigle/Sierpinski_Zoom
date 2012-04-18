#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "sierpinski_carpet.h"
#include "SOIL.h"

Carpet::Carpet(int levels) : levels(levels)
{
    texture = SOIL_load_OGL_texture("texture.bmp", SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
        SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    
    if (texture == 0)
        std::cout << "SOIL loading error: " << SOIL_last_result() << std::endl;
}

void Carpet::draw(double x, double y, double z, int level, double size)
{
    if (level == 0)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(x * 4, y * 4, z * 4);
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

void Carpet::draw(double size)
{
    draw(0.0, 0.0, 0.0, 3, size);
}
