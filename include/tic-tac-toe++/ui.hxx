#pragma once

#include <string>

#include <ncurses.h>

#include <tic-tac-toe++/Gameboard.hxx>
#include <tic-tac-toe++/Coord.hxx>

namespace txx {
    // analogous to 'addstr' in ncurses
    void printa(std::string a);
    void printa(std::string a, attr_t attr);

    void draw(const Gameboard& gb);

    // move the cursor to the specified collumn on the current row in win
    void moveX(int x, WINDOW* win=stdscr);

    // prompt player to enter information returned as a Coord
    Coord getCoord(WINDOW* win=stdscr);
}