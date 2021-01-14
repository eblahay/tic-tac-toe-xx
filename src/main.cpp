#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "BoardSettings.hpp"
#include "Gameboard.hpp"

void printHelpMenu();

inline std::string getVersion();

int main(int argc, char* argv[]){

    //initializing random seed
    srand(time(NULL));

    //initializing customizable members of gameboard
    BoardSettings settings;

    //succeeding for loop parses command line for arguments
    for(int i=1; i<argc; i++){
        //std::cout << "i = " << i << "\nargv[i] = " << argv[i] << "\n\n";
        if(std::strcmp(argv[i], "--help")==0){
            printHelpMenu();
            return 0;
        }
        else if(std::strcmp(argv[i], "--solo")==0 || std::strcmp(argv[i], "--singleplayer")==0){
            settings.singleplayer=true;
            if(std::strcmp(argv[i+1], "hard")==0){
                settings.difficulty = 1;
                i++;
            }
            else if(std::strcmp(argv[i+1], "easy")==0){
                settings.difficulty = 0;
                i++;
            }
            else{
                std::cout << "\033[31;1merror:\033[0m no difficulty specified.\n  type '--help' for a list of solo game difficulties.\n";
                return 1;
            }
            
        }
        else if(std::strcmp(argv[i], "-t")==0 || std::strcmp(argv[i], "--theme")==0){
            if(std::strcmp(argv[i+1], "classic")==0){
                settings.theme = {'0','1','2'};
                i++;
            }
            else if(std::strcmp(argv[i+1], "default")==0){
                /*
                since gameboard_theme is already intialized with the default theme,
                nothing needs to be done here.
                */
                i++;
            }
            else if(argv[i+1][1] == ',' && argv[i+1][3] == ',' && std::string(argv[i+1]).size() == 5){
                /*
                this section allows the user to define a custom theme with a command line arg.
                */
                settings.theme = {argv[i+1][0], argv[i+1][2], argv[i+1][4]};

                i++;
            }
            else{
                std::cout << "\033[31;1merror:\033[0m no theme specified.\n  type '--help' for a list of themes.\n";
                return 1;
            }
        }
        else if(strcmp(argv[i], "--version")==0){
            std::cout << "Tic-Tac-Toe++ version " << getVersion() << '\n';
            return 0;
        }
        else{
            std::cout << "\033[31;1merror:\033[0m unrecognized argument.\n  type '--help' for help.\n";
            return 1; 
        }
    }

    Gameboard gameboard(settings);

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

void printHelpMenu(){
    /*
    function that outputs a catalog of optional
    command-line arguments & their functions to the user to std::cout
    */

    std::cout <<
        " Tic-Tac-Toe++ version 0.3 help menu\n" <<
        "---------------------------------------\n" <<
        "FORM: Tic-Tac-Toe++ [OPTION 1] [OPTION 2] ...etc.\n"<<
        "---------------------------------------\n" <<
        "     --help          ....prints this menu\n" <<
        "     -t <theme>      ....sets the theme of the gameboard to <theme>\n" <<
        "        --theme <theme>\n" <<
        "                      default     ....the default theme\n" <<
        "                      classic     ....the theme from version 0.0.3.0\n" <<
        "                      X,Y,Z       ....defines a custom theme using X, Y and Z.\n" <<
        "                           e.g. '-t -,A,B'\n" <<
        "     -solo <difficulty>       ....launches the program in singleplayer mode with <difficulty> difficulty\n" <<
        "        --singleplayer <difficulty>\n" <<
        "                      valid difficulties: easy, hard\n" <<
        "     --version        ....prints the version of the program to the console\n" <<
        "---------------------------------------\n"
    ;
}

inline std::string getVersion(){
    return "0.3.0";
}