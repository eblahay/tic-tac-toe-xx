#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Coord.hpp"
#include "validators.hpp"
#include "player.hpp"


class Gameboard{
    public:
       constexpr static unsigned int \
            GAME_ONGOING = 0,
            P1_VICTORY = 1,
            P2_VICTORY = 2, 
            STALEMATE = 3
        ;

        constexpr static char \
            BLANK_MARK = ' ',
            PLAYER_MARKS[2] = {'X','O'}
        ;

        Gameboard(unsigned int width = 3, unsigned int height = 3);

        void handleInput();

        void draw(unsigned int vertical_offset=0);

        unsigned int getVictor();
        unsigned int determineVictor();
        unsigned int getTurnNumber();
        void toggleSimpleGrid();
        void changeTurn();
        void forceVictor(unsigned int n);
        char findMark(int x, int y);

    private:
        unsigned int width, height, victor=0, turn_holder=0, turn=1, player_number=2;
        /* 
            victor key: 0 = n/a, 1 = p1, 2 = p2, 3 = stalemate/tie
            turn_holder key: 0=p1, 1=p2
            turn: the total number of turns in the current round
        */
        bool simple_grid = false;
        std::vector<std::vector<char>> mark_arr;
        std::vector<std::unique_ptr<IPlayer>> players;
};

#endif