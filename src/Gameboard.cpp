#include "Gameboard.hpp"

#include <exception>

Gameboard::Gameboard(unsigned int width, unsigned int height){
    //intializing mark_arr
    this->width = width;
    this->height = height;

    for(int i=0; i<height; i++){
        std::vector<char> row;
        for(int j=0; j<width; j++){
            row.push_back(BLANK_MARK);
        }
        mark_arr.push_back(row);
    }

    //adding players
    players.push_back(std::make_unique<HumanPlayer>(this));
    players.push_back(std::make_unique<HumanPlayer>(this));

    megatato_debug::print("Gameboard has been initialized.");
}

void Gameboard::handleInput(){
    Coord des_space(0,0);

    bool collected_coord=false;
    while(!collected_coord){
        try{
            des_space = players[turn_holder]->pickDesCoord();
            collected_coord = true;
        }
        catch(std::runtime_error err){
            collected_coord = false;
        }
    }

    mark_arr[des_space.y()-1][des_space.x()-1] = PLAYER_MARKS[turn_holder];
    changeTurn();

}

void Gameboard::draw(unsigned int vertical_offset){
    for(int i=0; i<vertical_offset; i++) std::cout << '\n';

    std::cout << "Turn " << turn << ": It's Player " << turn_holder+1 << "'s turn!\n";

    if(!simple_grid){
        std::cout << "  ";
        for(int collumn=0; collumn<width; collumn++){
            std::cout << collumn+1;
            if(collumn < width-1) std::cout << ' ';
        }
        std::cout << '\n';
    }

    for(int row=0; row<height; row++){
        if(!simple_grid) std::cout << row+1 << " ";
        for(int collumn=0; collumn<width; collumn++){
            std::cout << mark_arr[row][collumn];
            if(collumn < width-1) std::cout << '|';
        }
        std::cout << '\n';
        if(row<height-1){
            if(!simple_grid) std::cout << "  ";
            for(int collumn=0; collumn < (width*2)-1; collumn++){
                std::cout<<'-';
            }
            std::cout << '\n';
        }
    }
}

unsigned int Gameboard::getVictor(){
    return victor;
}

unsigned int Gameboard::determineVictor(){
    megatato_debug::print("determining victory...");

    unsigned int result = Gameboard::GAME_ONGOING;

    int mark_streak_row = 0, blank_mark_tally = 0, dr_diag_tally=0, ul_diag_tally=0, collumn_same_mark_presence_arr[mark_arr[0].size()] = {0,0,0};

    for(int player=0; player<player_number && result==0; player++){
        for(int row=0; row<mark_arr.size(); row++){
            for(int collumn=0; collumn<mark_arr[row].size(); collumn++){
                if(mark_arr[row][collumn] == PLAYER_MARKS[player]){
                    mark_streak_row++;
                    collumn_same_mark_presence_arr[collumn]++;
                    if(row == collumn){
                        dr_diag_tally++;
                        if(collumn == 1) ul_diag_tally++;
                    }
                    else if((collumn == 0 && row == 2) || (collumn == 2 && row == 0)){
                        ul_diag_tally++;
                    }
                }
                else if(mark_arr[row][collumn] == BLANK_MARK) blank_mark_tally++;
            }
            if(mark_streak_row > 2 || dr_diag_tally > 2 || ul_diag_tally > 2){
                result = player+1;
                megatato_debug::print("Streak found!");
            }

            mark_streak_row = 0;
        }
        for(int collumn_mark_tally_arr_i=0; collumn_mark_tally_arr_i < mark_arr[0].size(); collumn_mark_tally_arr_i++){
            if(collumn_same_mark_presence_arr[collumn_mark_tally_arr_i] > 2){
                result = player+1;
                megatato_debug::print("Vertical streak found!");
            }
        }
        collumn_same_mark_presence_arr[0] = 0;
        collumn_same_mark_presence_arr[1] = 0;
        collumn_same_mark_presence_arr[2] = 0;

        dr_diag_tally = 0;
        ul_diag_tally = 0;
    }

    if(result==Gameboard::GAME_ONGOING && blank_mark_tally==0) result = Gameboard::STALEMATE;

    victor = result;
    return result;
}

void Gameboard::toggleSimpleGrid(){
    simple_grid=!simple_grid;
}

void Gameboard::changeTurn(){
    turn++;
    if(turn_holder+1 >= player_number) turn_holder = 0;
    else turn_holder++;
}

unsigned int Gameboard::getTurnNumber(){
    return turn;
}

void Gameboard::forceVictor(unsigned int n){
    victor = n;
}

char Gameboard::findMark(unsigned int x, unsigned int y){
    return mark_arr[y][x];
}