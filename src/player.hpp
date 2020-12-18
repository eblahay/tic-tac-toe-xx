#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

#include "Coord.hpp"

//forward decl for the sake of allow ptr to it in IPlayer
class Gameboard;
//

class IPlayer{
    public:
        IPlayer(Gameboard* gameboard){
            this->gameboard = gameboard;
        }
        //virtual ~IPlayer() = 0;

        virtual Coord pickDesCoord() = 0;

        virtual bool isCpu() = 0;
    protected:
        Gameboard* gameboard;
};

class HumanPlayer: public IPlayer{
    public:
        HumanPlayer(Gameboard* gameboard);
        
        Coord pickDesCoord();

        bool isCpu();
};

class CpuPlayer: public IPlayer{
    public:
        CpuPlayer(Gameboard* gameboard);
        
        Coord pickDesCoord();

        bool isCpu();
};

#endif