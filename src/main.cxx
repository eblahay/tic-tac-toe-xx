#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <boost/program_options.hpp>
#include <ncurses.h>

#include <tic-tac-toe++/BoardSettings.hxx>
#include <tic-tac-toe++/Gameboard.hxx>
#include <tic-tac-toe++/ui.hxx>

namespace po = boost::program_options;

inline std::string getVersion();

int main(int argc, char* argv[]){

    //initializing random seed
    srand(time(NULL));

    //initializing customizable members of gameboard
    BoardSettings settings;

    try{
        // parse command-line arguments
        po::options_description cmdln_opts("Options");
        cmdln_opts.add_options()
            ("help", "prints this message")
            ("version", "prints program version information")
            ("solo,s", po::value<std::string>(),"launches the program in singleplayer mode with the selected difficulty\n  valid difficulties: easy, hard")
            ("theme,t", po::value<std::string>(),"sets the theme of the gameboard\n  - default     ....the default theme\n  - classic     ....the theme from version 0.0.3.0\n  - X,Y,Z       ....defines a custom theme using X, Y and Z\n    e.g. '-t -,A,B'")
        ;

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(cmdln_opts).run(), vm);
        po::notify(vm);

        if(vm.count("help")){
            std::cout << "Usage: " << program_invocation_short_name << " [ options ... ]\n" << cmdln_opts << '\n';
        }
        else if(vm.count("version")){
            std::cout << "Tic-Tac-Toe++ " << getVersion() << '\n';
        }
        else{ // after arguments that cause the program to end
            // process the rest of the arguments
            if(vm.count("solo")){
                settings.singleplayer=true;
                if(vm["solo"].as<std::string>() == "hard"){
                    settings.difficulty = 1;
                }
                else if(vm["solo"].as<std::string>() == "easy"){
                    settings.difficulty = 0;
                }
                else{
                    throw std::runtime_error("\033[31;1mError:\033[0m no difficulty specified.\n  type '--help' for a list of solo game difficulties.");
                }
            }
            if(vm.count("theme")){
                if(vm["theme"].as<std::string>() == "classic"){
                    settings.marks = {'0','1','2'};
                    settings.axis_labels = false;
                }
                else if(vm["theme"].as<std::string>() == "default"){
                    /*
                    since gameboard_theme is already intialized with the default theme,
                    nothing needs to be done here.
                    */
                }
                else if(vm["theme"].as<std::string>()[1] == ',' && vm["theme"].as<std::string>()[3] == ',' && vm["theme"].as<std::string>().size() == 5){
                    /*
                    this section allows the user to define a custom theme with a command line arg.
                    */
                    settings.marks = {vm["theme"].as<std::string>()[0], vm["theme"].as<std::string>()[2], vm["theme"].as<std::string>()[4]};
                }
                else{
                    throw std::runtime_error("\033[31;1mError:\033[0m no theme specified.\n  type '--help' for a list of themes.");
                }
            }
            // end of argument parsing

            std::string conf_dir(getenv("HOME"));
            conf_dir += "/.tic-tac-toe-xx";

            //end of initialization

            Gameboard gameboard(settings);

            initscr(); // start ncurses mode

            noecho();
            keypad(stdscr, true);
            cbreak(); // line buffering disabled
            curs_set(0); // make the cursor invisible

            //event loop goes here
            txx::draw(gameboard);
            int winner;  
            do{
                gameboard.handleTurn();

                txx::draw(gameboard);

                winner = gameboard.findWinner();
            }
            while(winner == Gameboard::UNDECIDED);
            
            const std::string EN_NUMBERS[2] = {"O N E", "T W O"};

            addch(' ');

            if(winner == Gameboard::STALEMATE){
                addstr("S T A L E M A T E  \n    no one wins...\n");
            }
            else{
                txx::addStr(
                    "P L A Y E R  " +
                    EN_NUMBERS[winner] +
                    "  V I C T O R Y !",
                    A_BOLD | A_UNDERLINE
                );
            }
            
            getch(); // wait for player input

            endwin(); // end ncurses mode
        }

        return 0;
    }
    catch(std::exception &err){
        std::cerr << err.what() << '\n';
        return 1;
    }
}

inline std::string getVersion(){
    return "2.0.0";
}