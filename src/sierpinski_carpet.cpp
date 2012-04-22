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

using namespace std;


Carpet::Carpet(double size, int levels) : size(size), levels(levels)
{
    texture = SOIL_load_OGL_texture("texture.bmp", SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
        SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    
    if (texture == 0)
        std::cout << "SOIL loading error: " << SOIL_last_result() << endl;
    
    initBuffers();
}

void Carpet::initBuffers() {
    GLuint vbuffer;
    
    static const GLfloat data[] = {0.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,0.0f};
    
    glGenBuffers(1, &vbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, 0);
    
}

void Carpet::draw(double x, double y, double z, int level, double size)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES,0,3); 
}

void Carpet::draw()
{
    draw(0.0, 0.0, 0.0, levels, size);
}
