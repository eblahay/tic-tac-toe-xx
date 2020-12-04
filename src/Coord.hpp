#ifndef COORD_HPP
#define COORD_HPP

class Coord{
    public:
        Coord(unsigned int x, unsigned int y);

        unsigned int x();
        unsigned int y();
    private:
    unsigned int x_var, y_var;
};

#endif