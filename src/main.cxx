#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <tic-tac-toe++/BoardSettings.hxx>
#include <tic-tac-toe++/Gameboard.hxx>

void printHelpMenu();

inline std::string getVersion();

int main(int argc, char* argv[]){

    //initializing random seed
    srand(time(NULL));

    //initializing customizable members of gameboard
    BoardSettings settings;

    try{
        //succeeding for loop parses command line for arguments
        for(int i=1; i<argc; i++){
            //std::cout << "i = " << i << "\nargv[i] = " << argv[i] << "\n\n";
            if(std::strcmp(argv[i], "--help")==0){
                printHelpMenu();
                return 0;
            }
            else if(std::strcmp(argv[i], "-s")==0 || std::strcmp(argv[i], "--singleplayer")==0){
                settings.singleplayer=true;
                if(i+1 >= argc){
                    throw std::runtime_error("\033[31;1merror:\033[0m no difficulty specified.\n  type '--help' for a list of solo game difficulties.");
                }
                else if(std::strcmp(argv[i+1], "hard")==0){
                    settings.difficulty = 1;
                    i++;
                }
                else if(std::strcmp(argv[i+1], "easy")==0){
                    settings.difficulty = 0;
                    i++;
                }
                else{
                    throw std::runtime_error("\033[31;1merror:\033[0m no difficulty specified.\n  type '--help' for a list of solo game difficulties.");
                }
                
            }
            else if(std::strcmp(argv[i], "-t")==0 || std::strcmp(argv[i], "--theme")==0){
                if(i+1 >= argc){
                    throw std::runtime_error("\033[31;1merror:\033[0m no theme specified.\n  type '--help' for a list of themes.");
                }
                else if(std::strcmp(argv[i+1], "classic")==0){
                    settings.theme = {'0','1','2'};
                    settings.axis_labels = false;
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
                    throw std::runtime_error("\033[31;1merror:\033[0m no theme specified.\n  type '--help' for a list of themes.");
                }
            }
            else if(strcmp(argv[i], "--version")==0){
                std::cout << "Tic-Tac-Toe++ version " << getVersion() << '\n';
                return 0;
            }
            else{
                throw std::runtime_error("\033[31;1merror:\033[0m unrecognized argument.\n  type '--help' for help.");
            }
        }
    }
    catch(std::exception &err){
        std::cerr << err.what() << '\n';
        return 1;
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
        " Tic-Tac-Toe++ help menu\n" <<
        "---------------------------------------\n" <<
        "Usage: Tic-Tac-Toe++ [options]\n"<<
        "---------------------------------------\n" <<
        "     --help          ....prints this menu\n" <<
        "     -t <theme>      ....sets the theme of the gameboard to <theme>\n" <<
        "        --theme <theme>\n" <<
        "                      default     ....the default theme\n" <<
        "                      classic     ....the theme from version 0.0.3.0\n" <<
        "                      X,Y,Z       ....defines a custom theme using X, Y and Z.\n" <<
        "                           e.g. '-t -,A,B'\n" <<
        "     -s <difficulty>       ....launches the program in singleplayer mode with <difficulty> difficulty\n" <<
        "        --singleplayer <difficulty>\n" <<
        "                      valid difficulties: easy, hard\n" <<
        "     --version        ....prints the version of the program to the console\n" <<
        "---------------------------------------\n"
    ;
}

inline std::string getVersion(){
    return "1.2.0";
}