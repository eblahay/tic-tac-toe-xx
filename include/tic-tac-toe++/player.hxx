#pragma once

#include <iostream>

#include <tic-tac-toe++/Coord.hxx>

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

class CpuPlayerEasy: public PlayerBase{
    public:
        CpuPlayerEasy(Gameboard* gameboard);
        
        Coord pickDesCoord();

        bool isCpu();
};

class CpuPlayerHard: public PlayerBase{
    public:
        CpuPlayerHard(Gameboard* gameboard);
        
        Coord pickDesCoord();

        bool isCpu();
};