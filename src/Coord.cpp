#include "Coord.hpp"

Coord::Coord(unsigned int x, unsigned int y){
    x_var = x;
    y_var = y;
}

unsigned int Coord::x(){
    return x_var;
}

unsigned int Coord::y(){
    return y_var;
}