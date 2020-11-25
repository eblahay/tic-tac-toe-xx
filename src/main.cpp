#include <iostream>
#include <cstring>

#include "GameBoard.hpp"

int main(int argc, char* argv[]){

    Gameboard gameboard(3, 3);

    for(int i=0; i<argc; i++){
        if(std::strcmp(argv[i], "--simple_grid")==0) gameboard.toggleSimpleGrid();
    }

    gameboard.draw();
    do{

        gameboard.handleInput();

        gameboard.draw(1);
    }
    while(gameboard.determineVictor()==Gameboard::GAME_ONGOING);

    if(gameboard.getVictor()!=Gameboard::STALEMATE){
        std::cout << "Player " << gameboard.getVictor() << " wins!\n";
    }
    else{
        std::cout << "\nSTALEMATE!\n";
    }
    std::cout << "Game Duration: " << gameboard.getTurnNumber() << " turns.\n";

    return 0;
}