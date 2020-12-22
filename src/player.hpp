#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

#include "Coord.hpp"

//forward decl to allow ptr to it in PlayerBase
class Gameboard;
//

class PlayerBase{
    public:
        PlayerBase(Gameboard* gameboard);

        virtual Coord pickDesCoord() = 0;

        virtual bool isCpu() = 0;

        void setMark(char mark);

        char getMark();
 protected:
        const Gameboard* gameboard;
        char mark;
};

class HumanPlayer: public PlayerBase{
    public:
        HumanPlayer(Gameboard* gameboard);
        
        Coord pickDesCoord();

        bool isCpu();
};

class CpuPlayer: public PlayerBase{
    public:
        CpuPlayer(Gameboard* gameboard);
        
        Coord pickDesCoord();

        bool isCpu();
};

#endif