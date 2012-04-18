class Carpet
{
    public:
        Carpet(double size, int levels);
        void draw();

    private:
        void draw(double x, double y, double z, int level, double size);
        double size;
        int levels;
};
