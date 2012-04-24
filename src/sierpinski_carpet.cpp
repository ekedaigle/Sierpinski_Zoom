#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define CUBE_VERTICES 12

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "sierpinski_carpet.h"

using namespace std;


Carpet::Carpet(int levels) : levels(levels)
{
    initBuffer();
}

void Carpet::initBuffer() {
    
    SVertex * vertices;
    int vertices_needed;
    
    // Allocate vertex generation array (recursion complexity ^ recursion depth) * base * corner detail
    vertices_needed = pow((double)17, levels)*CUBE_VERTICES*4; 
    vertices = (SVertex *) calloc(vertices_needed, sizeof(SVertex));
    
    // Generate all the sub-cube vertices
    vertex_count = generate(0.0, 0.0, 0.0, levels, 3, 1.0f, vertices, 0);
//    vertex_count = cube(0.0f, 0.0f, 0.0f, 1.0f, vertices, 0);

    printf("vertices:%i\n", vertex_count);
    
    // Put vertices in buffer
    glGenBuffers(1, &vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex)*vertex_count, vertices, GL_STATIC_DRAW);
    
    // Use positions from buffer 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(SVertex), 0);
    
//    // Use colors from buffer 
//    glEnableClientState(GL_COLOR_ARRAY);
//    glColorPointer(3, GL_FLOAT, sizeof(SVertex), (GLvoid *) offsetof(SVertex, r));
    
    // Use normals from buffer 
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(SVertex), (GLvoid *) offsetof(SVertex, nx));
    
    free(vertices);
}

int Carpet::generate(double x, double y, double z, int level, int corner, double size, SVertex * vertices, int next)
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
            // skip center
            if (i == 0 && j == 0)
                continue;
            
            for (int k = -1; k <= 1; k++)
            {
                // skip center
                if ((i == 0 && k == 0) || (j == 0 && k == 0)) continue;
                
                // back corner isn't visible 
                if (i < 1 && k < 1 && j < 1) continue;
                
                // extra detail on the corner 
                int next_corner;
                int next_level;
                if (i == 1 && k == 1 && j == 1 && corner > 0) {
                    next_corner = corner - 1;
                    next_level = level;
                } else {
                    next_corner = 0;
                    next_level = level - 1;
                }
                
                next = generate(x + i * next_size, y + j * next_size, z + k * next_size, next_level, next_corner, next_size, vertices, next);
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
    
    //   y
    //   | 
    //   o-x
    //  /
    // z 

    
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
    static const GLfloat cubeVertices[CUBE_VERTICES*3] =
    {
        -1.0, +1.0, +1.0,  -1.0, -1.0, +1.0,  +1.0, -1.0, +1.0,  +1.0, +1.0, +1.0,   // v0-v1-v3-v2
        +1.0, +1.0, +1.0,  +1.0, -1.0, +1.0,  +1.0, -1.0, -1.0,  +1.0, +1.0, -1.0,   // v2-v3-v5-v4
//        +1.0, +1.0, -1.0,  +1.0, -1.0, -1.0,  -1.0, -1.0, -1.0,  -1.0, +1.0, -1.0,   // v4-v5-v7-v6
//        -1.0, +1.0, -1.0,  -1.0, -1.0, -1.0,  -1.0, -1.0, +1.0,  -1.0, +1.0, +1.0,   // v6-v7-v1-v0
        -1.0, +1.0, +1.0,  +1.0, +1.0, +1.0,  +1.0, +1.0, -1.0,  -1.0, +1.0, -1.0   // v0-v2-v4-v6
//        -1.0, +1.0, -1.0,  -1.0, -1.0, -1.0,  -1.0, -1.0, +1.0,  -1.0, +1.0, +1.0    // v3-v1-v7-v5
    };
    
    // vertex coords array
    static const GLfloat cubeNormals[3*3] =
    {
         0.0,  0.0, +1.0, // v0-v1-v3-v2
        +1.0,  0.0,  0.0, // v2-v3-v5-v4
//         0.0,  0.0, -1.0 // v4-v5-v7-v6
//        +1.0,  0.0,  0.0, // v6-v7-v1-v0
         0.0, +1.0,  0.0 // v0-v2-v4-v6
//         0.0, -1.0,  0.0  // v3-v1-v7-v5
    };
    
    double half = size/2;
    
    for (int i = 0; i < CUBE_VERTICES; i++) {
        SVertex * vertex = &(vertices[next+i]);
        vertex->x = cubeVertices[i*3+0] * half + x;
        vertex->y = cubeVertices[i*3+1] * half + y;
        vertex->z = cubeVertices[i*3+2] * half + z;
        int v = i/4; 
        vertex->nx = cubeNormals[v+0];
        vertex->ny = cubeNormals[v+1];
        vertex->nz = cubeNormals[v+2];
    }
    
    return next + CUBE_VERTICES;
}


void Carpet::draw(double size)
{
    glPushMatrix();
    glScalef(size,size,size);
    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_QUADS,0,vertex_count);
    glPopMatrix();
}
