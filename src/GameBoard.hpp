#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <iostream>
#include <vector>
#include <string>

#include "../../megatato_debug_api/headers/megatato_debug_api.hpp"

const char \
    BLANK_MARK = ' ',
    PLAYER_MARKS[2] = {'X','O'}
;

class Gameboard{
    public:
        const static unsigned int \
            GAME_ONGOING = 0,
            P1_VICTORY = 1,
            P2_VICTORY = 2, 
            STALEMATE = 3
        ;

        Gameboard(unsigned int width = 3, unsigned int height = 3);

        void handleInput();

        void draw(unsigned int vertical_offset);

        bool validateCoordStr(std::string input);
        unsigned int getVictor();
        void changeTurn();
        
    private:
        unsigned int width, height, victor=0, turn_holder=0, turn=1, player_number=2;
        /* 
            victor key: 0 = n/a, 1 = p1, 2 = p2, 3 = stalemate/tie
            turn_holder key: 0=p1, 1=p2
            turn: the total number of turns in the current round
        */
        std::vector<std::vector<char>> mark_arr;
};
Gameboard::Gameboard(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;

    for(int i=0; i<height; i++){
        std::vector<char> row;
        for(int j=0; j<width; j++){
            row.push_back(BLANK_MARK);
        }
        mark_arr.push_back(row);
    }

    megatato_debug::print("Gameboard has been initialized.");
}

void Gameboard::handleInput(){
    std::string e;
    std::getline(std::cin, e);

    unsigned int x, y;
    
    megatato_debug::setBoolAlpha();
    if(validateCoordStr(e)){
        x = std::stoi(e.substr(0, e.find(',')));
        y = std::stoi(e.substr(e.find(',')+1));

        if(mark_arr[y-1][x-1]==BLANK_MARK){
            mark_arr[y-1][x-1] = PLAYER_MARKS[turn_holder];
            changeTurn();
        }
        else std::cout << "Space Taken!\n";
    }
    else if(e == "/end") victor = 3;
    else std::cout << "Invalid Input\n";
}

void Gameboard::draw(unsigned int vertical_offset=0){
    for(int i=0; i<vertical_offset; i++) std::cout << '\n';

    std::cout << "It's Player " << turn_holder+1 << "'s turn!\n";

    for(int row=0; row<height; row++){
        for(int collumn=0; collumn<width; collumn++){
            std::cout << mark_arr[row][collumn];
            if(collumn < width-1) std::cout << '|';
        }
        std::cout << '\n';
        if(row<height-1){
            for(int collumn=0; collumn < (width*2)-1; collumn++){
                std::cout<<'-';
            }
            std::cout << '\n';
        }
    }
}

bool Gameboard::validateCoordStr(std::string input){
    bool result = false;

    if(input.find(',') != std::string::npos){
        try{
            int x = std::stoi(input.substr(0, input.find(','))), y = std::stoi(input.substr(input.find(',')+1));
            result = true;
        }
        catch(std::exception e){
            result = false;
            megatato_debug::print("There was an exception during CoordStr validation.");
        }
    }

    return result;
}

unsigned int Gameboard::getVictor(){
    return victor;
}

void Gameboard::changeTurn(){
    turn++;
    if(turn_holder+1 >= player_number) turn_holder = 0;
    else turn_holder++;
}

#endif