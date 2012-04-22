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
        void draw(double x, double y, double z, int level, double size);
    void initBuffers();
        double size;
        int levels;
        GLuint texture;
};
