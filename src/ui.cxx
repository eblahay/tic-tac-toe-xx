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
    move(0,0);
    addstr("It's ");
    addStr("Player " + std::to_string(gb.getTurnHolderIndex()+1), A_BOLD);
    addstr("'s turn!");
    move(2,0);
    
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

Coord txx::getCoord(WINDOW* win){
    int x=0, y=0;
    const int 
        LINE_START=getcurx(win),
        START_Y=getcury(win)
    ;

    bool getting_input=true;
    while(getting_input){
        curs_set(1); // make cursor visible
        echo();

        while((x > '3' || x < '1') || (y > '3' || y < '1')){
            move(START_Y, LINE_START);
            addstr("X: _ Y: _");
            for(int i=9; i<21; i++) addch(' ');

            moveX(LINE_START + 3);
            x = getch();

            moveX(LINE_START + 8);
            y = getch();
        }
        
        moveX(LINE_START);
        std::string
            coordinate_str = {'(',(char)x,',',(char)y,')'},
            prefix = "Select Space ",
            optstr[2] = {"Yes", "No"},
            optstr_key[2] = {"ENTER", "N"};
        ;
        addStr(prefix);
        addStr(coordinate_str, A_BOLD);
        addch('?');
        moveDn();
        moveX(LINE_START);
        addStr(optstr[0] + " [" + optstr_key[0] + "]");
        move(getcury(stdscr)+1, LINE_START);
        addStr(optstr[1] + " [" + optstr_key[1] + "]");

        curs_set(0); // make cursor invisible again
        noecho();

        bool b=true;
        while(b){
            int yn = getch();
            switch (yn) {
                case '\n':
                case KEY_ENTER:
                    getting_input = false;
                    x -= '1';
                    y -= '1';
                    y = 2 - y;

                    b=false;
                    moveX(LINE_START);
                    for(int i=0; i < optstr[1].size() + optstr_key[1].size() + 3; i++){
                        addch(' ');
                    }
                    moveDn(-1);
                    moveX(LINE_START);
                    for(int i=0; i < optstr[0].size() + optstr_key[0].size() + 3; i++){
                        addch(' ');
                    }

                    break;
                case 'n':
                case 'N':
                    x = 0;
                    y = 0;

                    b=false;
                    moveX(LINE_START);
                    for(int i=0; i < optstr[1].size() + optstr_key[1].size() + 3; i++){
                        addch(' ');
                    }
                    moveDn(-1);
                    moveX(LINE_START);
                    for(int i=0; i < optstr[0].size() + optstr_key[0].size() + 3; i++){
                        addch(' ');
                    }

                    break;
            }
        }
    }

    move(START_Y, LINE_START);
    for(int col=0; col < getmaxx(win); col++) addch(' ');
    
    move(START_Y, LINE_START); // fixes bug #0

    return Coord(x, y);
}