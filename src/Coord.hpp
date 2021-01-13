#ifndef COORD_HPP
#define COORD_HPP

class Coord{
    public:
        Coord(int x=0, int y=0);

        void setX(int x);
        void setY(int y);
        //function that alters coordinate values to match those of the src.
        void copy(const Coord &src);

        int x() const ;
        int y() const ;

    private:
        int _x, _y;
};

#endif