#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define CUBE_VERTICES 24

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
    
    initBuffer();
}

void Carpet::initBuffer() {
    
    SVertex * vertices;
    int vertices_needed;
    
    // Allocate vertex generation array (recursion complexity ^ recursion depth) * base
    vertices_needed = pow((double)20, levels)*CUBE_VERTICES; 
    vertices = (SVertex *) calloc(vertices_needed, sizeof(SVertex));
    
    // Generate all the sub-cube vertices
    vertex_count = generate(0.0, 0.0, 0.0, levels, size, vertices, 0);
//    vertex_count = cube(0.0f, 0.0f, 0.0f, 1.0f, vertices, 0);

    printf("vertices:%i\n", vertex_count);
    
    // Put vertices in buffer
    glGenBuffers(1, &vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex)*vertex_count, vertices, GL_STATIC_DRAW);
    
    // Use positions from buffer 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(SVertex), 0);
    
    // Use colors from buffer 
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(SVertex), (GLvoid *) offsetof(SVertex, r));
    
    free(vertices);
    
}

int Carpet::generate(double x, double y, double z, int level, double size, SVertex * vertices, int next)
{
    if (level == 0)
    {
        
        return cube(x,y,z,size,vertices,next);
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
                
                next = generate(x + i * next_size, y + j * next_size, z + k * next_size, level - 1, next_size, vertices, next);
            }
        }
    }
    
    return next;
}

int Carpet::cube(double x, double y, double z, double size, SVertex * vertices, int next) {
    
    // Cube stuff is mostly from - http://playcontrol.net/ewing/jibberjabber/opengl_vertex_buffer_object.html
    
    //    v6----- v4
    //   /|      /|
    //  v0------v2|
    //  | |     | |
    //  | |v7---|-|v5
    //  |/      |/
    //  v1------v3
    
    /*
     v0:
     -1.0, +1.0, +1.0,
     
     v1:
     -1.0, -1.0, +1.0,
     
     v2:
     +1.0, +1.0, +1.0,
     
     v3:
     +1.0, -1.0, +1.0,
     
     v4:
     +1.0, +1.0, -1.0,
     
     v5:
     +1.0, -1.0, -1.0,
     
     v6:
     -1.0, +1.0, -1.0,
     
     v7:
     -1.0, -1.0, -1.0,
     */
    
    // vertex coords array
    static const GLfloat cubeVertices[72] =
    {
        -1.0, +1.0, +1.0,  -1.0, -1.0, +1.0,  +1.0, -1.0, +1.0,  +1.0, +1.0, +1.0,   // v0-v1-v3-v2
        +1.0, +1.0, +1.0,  +1.0, -1.0, +1.0,  +1.0, -1.0, -1.0,  +1.0, +1.0, -1.0,   // v2-v3-v5-v4
        +1.0, +1.0, -1.0,  +1.0, -1.0, -1.0,  -1.0, -1.0, -1.0,  -1.0, +1.0, -1.0,   // v4-v5-v7-v6
        -1.0, +1.0, -1.0,  -1.0, -1.0, -1.0,  -1.0, -1.0, +1.0,  -1.0, +1.0, +1.0,   // v6-v7-v1-v0
        -1.0, +1.0, +1.0,  +1.0, +1.0, +1.0,  +1.0, +1.0, -1.0,  -1.0, +1.0, -1.0,   // v0-v2-v4-v6
        -1.0, +1.0, -1.0,  -1.0, -1.0, -1.0,  -1.0, -1.0, +1.0,  -1.0, +1.0, +1.0    // v3-v1-v7-v5
    };
    
    double half = size/2;
    
    for (int i = 0; i < CUBE_VERTICES; i++) {
        SVertex * vertex = &(vertices[next+i]);
        vertex->x = cubeVertices[i*3+0] * half + x;
        vertex->y = cubeVertices[i*3+1] * half + y;
        vertex->z = cubeVertices[i*3+2] * half + z;
        vertex->r = x/this->size;
        vertex->g = y/this->size;
        vertex->b = z/this->size;
    }
    
    
    
//    memcpy(&(vertices[next]), realVertices, sizeof(realVertices));
    
    return next + CUBE_VERTICES;
}


void Carpet::draw()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_QUADS,0,vertex_count);
}
