#include "Coord.hpp"

Coord::Coord(int x, int y){
    x_var = x;
    y_var = y;
}

int Coord::x(){
    return x_var;
}

int Coord::y(){
    return y_var;
}