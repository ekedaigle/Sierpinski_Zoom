#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

class Carpet
{
    public:
        Carpet(double size, int levels);
        void draw();

    private:
        struct SVertex
        {
            GLfloat x,y,z;
            GLfloat nx,ny,nz;
        };

        int generate(double x, double y, double z, int level, double size, SVertex * vertices, int next);
        int cube(double x, double y, double z, double size, SVertex * vertices, int next);
        void initBuffer();
        double size;
        int levels;
        int vertex_count;
        GLuint vbuffer;
        GLuint texture;
};
