#include <iostream>

#include "GameBoard.hpp"

int main(){
    Gameboard gameboard(3, 3);

    gameboard.draw();
    while(gameboard.getVictor()==Gameboard::GAME_ONGOING){

        gameboard.handleInput();

        gameboard.draw(1);
    }
    if(gameboard.getVictor()!=Gameboard::STALEMATE){
        std::cout << "Player " << gameboard.getVictor() << " wins!\n";
    }
    else{
        std::cout << "\nSTALEMATE!\n";
    }

    return 0;
}