#ifndef COORD_HPP
#define COORD_HPP

class Coord{
    public:
        Coord(int x, int y);

        int x();
        int y();
    private:
        int x_var, y_var;
};

#endif