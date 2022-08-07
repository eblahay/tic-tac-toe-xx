#include <tic-tac-toe++/Coord.hxx>

Coord::Coord(int x, int y):
    _x(x),
    _y(y)
{
}

int Coord::x() const {
    return _x;
}

int Coord::y() const {
    return _y;
}

void Coord::setX(int x){
    _x = x;
}

void Coord::setY(int y){
    _y = y;
}

void Coord::copy(const Coord &src){
    setX(src._x);
    setY(src._y);
}