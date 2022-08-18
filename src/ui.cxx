#include <cstddef>
#include <curses.h>
#include <string>
#include <tic-tac-toe++/ui.hxx>

void txx::addStr(std::string a){
    for(auto it=a.begin(); it != a.end(); it++){
        addch(*it);
    }
}
void txx::addStr(std::string a, attr_t attr){
    attron(attr);
    addStr(a);
    attroff(attr);
}

void txx::draw(const Gameboard& gb){
    // draw playerlist
    move(0,0);
    for(int i=0; i<2; i++){
        std::string ln;
        ln.push_back(' ');
        ln.push_back(gb.SETTINGS.marks[i+1]);
        ln.push_back(' ');
        ln += "Player " + std::to_string(i+1);
        ln.push_back(' ');
        
        if(i == gb.getTurnHolderIndex()) addStr(ln, A_REVERSE);
        else addStr(ln);

        move(getcury(stdscr)+1,0);
    }
    
    // draw board
    move(3,0);
    for(int row=0; row<gb.getBoardHeight(); row++){
        if(gb.SETTINGS.axis_labels){
            addch(gb.SETTINGS.axis_nums[gb.getBoardHeight()-row-1] | A_DIM);
            addch(' ');
        }
        for(int width=0; width<gb.getBoardWidth(); width++){
            if(gb.SETTINGS.axis_labels){
                if(row < gb.getBoardHeight() - 1) attron(A_UNDERLINE);
                addch(gb.getMark(width, row));
                if(width != gb.getBoardWidth() - 1){
                    addch('|');
                }
                if(row < gb.getBoardHeight() - 1) attroff(A_UNDERLINE);
            }
            else addch(gb.getMark(width, row));
        }
        move(getcury(stdscr)+1, 0);
    }
    if(gb.SETTINGS.axis_labels){
        addstr("  ");
        
        for(int width=0;width<gb.getBoardWidth(); width++){
            addch(gb.SETTINGS.axis_nums[width] | A_DIM);
            addch(' ');
        }
        move(getcury(stdscr)+1, 0);
    }

    move(getcury(stdscr)+1, 0);

    refresh();
}

void txx::moveX(int x, WINDOW* win){
    move(getcury(win), x);
}

void txx::moveDn(int d, WINDOW* win){
    move(getcury(win) + d, getcurx(win));
}

Coord txx::getCoord(const Gameboard* gb, WINDOW* win){
    int x=1, y=1; // initial coordinate selection

    const int BOARD_Y = 3;

    bool selecting = true;
    while(selecting){
        // move to and highlight selected space onscreen
        if(!gb->SETTINGS.axis_labels) move(BOARD_Y + y, x);
        else{
            move(BOARD_Y + y, (x * 2) + 2);

            if(y != 2) attron(A_UNDERLINE);
            else attroff(A_UNDERLINE);
        }
        addch(gb->getMark(x, y) | A_REVERSE);

        // collect input
        int c = getch();

        // un-highlight selected space onscreen
        moveX(getcurx(win)-1);
        addch(gb->getMark(x, y));

        attroff(A_UNDERLINE); // turn off underline

        // process input
        switch (c) {
            case KEY_ENTER:
            case '\n':
                selecting = false;
                break;
            
            case KEY_UP:
            case 'W':
            case 'w':
                if(y-1 >= 0) y--;
                break;

            case KEY_DOWN:
            case 'S':
            case 's':
                if(y+1 < 3) y++;
                break;

            case KEY_LEFT:
            case 'A':
            case 'a':
                if(x-1 >= 0) x--;
                break;

            case KEY_RIGHT:
            case 'D':
            case 'd':
                if(x+1 < 3) x++;
                break;

            default:

                break;
        }
    }

    return Coord(x, y);
}