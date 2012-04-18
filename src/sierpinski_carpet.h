#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

class Carpet
{
    public:
        Carpet(int levels);
        void draw(double size);

    private:
        void draw(double x, double y, double z, int level, double size);
        int levels;
        GLuint texture;
};
