#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Gameboard.hpp"

int printHelpMenu();

int main(int argc, char* argv[]){

    //initializing random seed
    srand(time(NULL));

    //initializing customizable members of gameboard
    std::vector<char> gameboard_theme = {'_','X','O'};
    bool singleplayer=false;

    //succeeding for loop parses command line for arguments
    for(int i=0; i<argc; i++){
        if(std::strcmp(argv[i], "-h")==0) return printHelpMenu();
        else if(std::strcmp(argv[i], "-solo")==0 || std::strcmp(argv[i], "--singleplayer")==0){
            singleplayer=true;
        }
        else if(std::strncmp(argv[i], "-theme=", 7)==0){
            if(std::strcmp(argv[i], "-theme=classic")==0) gameboard_theme = {'0','1','2'};
            else if(std::strcmp(argv[i], "-theme=default")==0){
                /*
                since gameboard_theme is already intialized with the default theme,
                nothing needs to be done here.
                */
            }
        }
    }

    Gameboard gameboard(singleplayer, gameboard_theme);

    //event loop goes here
    gameboard.drawBoard();
    do{
        gameboard.handleTurn();

        gameboard.drawBoard();
    }
    while(gameboard.findWinner() == Gameboard::UNDECIDED);
    
    int winner = gameboard.findWinner();
    const char* EN_NUMBERS[2] = {"O N E", "T W O"};

    if(winner == Gameboard::STALEMATE){
        std::cout << "  S T A L E M A T E  \n    no one wins...\n";
    }
    else{
        std::cout << "  P L A Y E R  " << EN_NUMBERS[winner] << "  V I C T O R Y !\n";
    }

    return 0;
}

int printHelpMenu(){
    /*
    function that outputs a catalog of optional
    command-line arguments & their functions to the user to std::cout
    */

    std::cout <<
        " Tic-Tac-Toe++ α version 0.2 help menu\n" <<
        "---------------------------------------\n" <<
        "     -h          ....prints this menu\n" <<
        "     -theme=     ....sets the theme of the gameboard to the following value\n" <<
        "          default     ....the default theme\n" <<
        "          classic     ....the theme from version 0.0.3.0\n" <<
        "     -solo       ....launches the program in singleplayer mode\n" <<
        "          --singleplayer\n" <<
        "---------------------------------------\n"
    ;

    return 0;
}