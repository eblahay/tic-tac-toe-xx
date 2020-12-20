#include "player.hpp"

#include <exception>
#include "Gameboard.hpp"

//HumanPlayer

HumanPlayer::HumanPlayer(Gameboard* gameboard): IPlayer::IPlayer(gameboard){
    
}

Coord HumanPlayer::pickDesCoord(){
    std::string e;
    std::getline(std::cin, e);

    int x, y;
    
    megatato_debug::setBoolAlpha();
    if(validators::inputCoordValidator(e)){
        x = std::stoi(e.substr(0, e.find(',')));
        y = std::stoi(e.substr(e.find(',')+1));

        std::cout << "x: " << x << ", y: " << y <<'\n';

        if(gameboard->findMark(x-1, y-1) == Gameboard::BLANK_MARK);
        else{
            std::cout << "Space Taken!\n";
            throw std::runtime_error("Invalid Input");
        }
    }
    else if(e == "/end") gameboard->forceVictor(3);
    else{
        std::cout << "Invalid Input\n";
        throw std::runtime_error("Invalid Input");
    }

    return Coord(x, y);
}

bool HumanPlayer::isCpu(){
    return false;
}

//CpuPlayer

CpuPlayer::CpuPlayer(Gameboard* gameboard): IPlayer::IPlayer(gameboard){
    
}

Coord CpuPlayer::pickDesCoord(){
    return Coord(2,2);
}

bool CpuPlayer::isCpu(){
    return true;
}