#include "player.hpp"

#include <exception>

#include "Gameboard.hpp"
#include "validators.hpp"

//PlayerBase
PlayerBase::PlayerBase(Gameboard* gameboard):
    gameboard(gameboard),
    mark('?')
{
    
}

void PlayerBase::setMark(char mark){
    this->mark = mark;
}

char PlayerBase::getMark(){
    return mark;
}

//HumanPlayer

HumanPlayer::HumanPlayer(Gameboard* gameboard): PlayerBase::PlayerBase(gameboard){
    
}

Coord HumanPlayer::pickDesCoord(){
    Coord result;

    std::string e;
    std::getline(std::cin, e);

    if(validators::inputCoordValidator(e)){
        result.setX(std::stoi(e.substr(0, e.find(','))) - 1);
        result.setY(gameboard->getBoardHeight() - std::stoi(e.substr(e.find(',')+1)));
    }
    else{
        throw std::runtime_error("Invalid Input");
    }

    return result;
}

bool HumanPlayer::isCpu(){
    return false;
}

//CpuPlayer

CpuPlayer::CpuPlayer(Gameboard* gameboard): PlayerBase::PlayerBase(gameboard){
    
}

Coord CpuPlayer::pickDesCoord(){
    return Coord(2,2);
}

bool CpuPlayer::isCpu(){
    return true;
}