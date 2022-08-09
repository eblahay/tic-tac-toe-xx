#include <curses.h>
#include <string>
#include <tic-tac-toe++/ui.hxx>

void txx::printa(std::string a){
    for(auto it=a.begin(); it != a.end(); it++){
        addch(*it);
    }
}
void txx::printa(std::string a, attr_t attr){
    attron(attr);
    printa(a);
    attroff(attr);
}

void txx::draw(const Gameboard& gb){
    move(0,0);
    addstr("It's ");
    printa("Player " + std::to_string(gb.getTurnHolderIndex()+1), A_BOLD);
    addstr("'s turn!");
    move(2,0);
    
    for(int row=0; row<gb.getBoardHeight(); row++){
        if(gb.axisLabels()){
            addch(gb.SETTINGS.axis_nums[gb.getBoardHeight()-row-1] | A_DIM);
            addch(' ');
        }
        for(int width=0; width<gb.getBoardWidth(); width++){
            if(gb.axisLabels()){
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
    if(gb.axisLabels()){
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

Coord txx::getCoord(WINDOW* win){
    int x=0, y=0;
    const int LINE_START=getcurx(win);

    echo();
    curs_set(1); // make cursor visible

    bool getting_input=true;
    while(getting_input){
        while((x > '3' || x < '1') || (y > '3' || y < '1')){
            moveX(LINE_START);
            addstr("X: _ Y: _");

            moveX(LINE_START + 3);
            x = getch();

            moveX(LINE_START + 8);
            y = getch();
        }
        
        moveX(LINE_START);
        addstr("Select Space ");
        std::string a = {'(',(char)x,',',(char)y,')'};
        printa(a, A_BOLD);
        addstr("? ");
        int yn = getch();

        switch (yn) {
            case '\n':
            case 'Y':
            case 'y':
                getting_input = false;
                x -= '1';
                y -= '1';
                y = 2 - y;
                
                break;
            default:
                x = 0;
                y = 0;
                break;
        }
    }

    noecho();
    curs_set(0); // make cursor invisible again

    moveX(LINE_START);
    for(int col=0; col < getmaxx(win); col++) addch(' ');

    return Coord(x, y);
}