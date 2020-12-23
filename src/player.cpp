#include "player.hpp"

#include <exception>
#include <stdlib.h>

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

    Coord result(rand() % gameboard->getBoardWidth(), rand() % gameboard->getBoardHeight());

    bool deciding=true;

    int
        foe_col_count = 0,
        foe_occ_spc_y_vals[2] = {-1,-1},
        self_col_count = 0,
        self_occ_spc_y_vals[2] = {-1,-1}
    ;

    for(int row=0; deciding && row < gameboard->getBoardHeight(); row++){
        int 
            foe_row_count = 0,
            foe_occ_spc_x_vals[2] = {-1,-1},
            self_row_count = 0,
            self_occ_spc_x_vals[2] = {-1,-1}
        ;

        for(int collumn=0; collumn < gameboard->getBoardWidth(); collumn++){
            if(gameboard->getMark(collumn, row) == this->getMark()){
                self_occ_spc_x_vals[self_row_count] = collumn;
                self_row_count++;
            }
            else if(gameboard->getMark(collumn, row) != gameboard->MARKS[0] && gameboard->getMark(collumn, row) != this->getMark()){
                foe_occ_spc_x_vals[foe_row_count] = collumn;
                foe_row_count++;
            }
        }

        if(self_row_count + foe_row_count < gameboard->getBoardWidth()){
            //change to result is only made if the row isn't full of player marks

            if(self_row_count == 2){
                result.setX(gameboard->getBoardWidth()-(self_occ_spc_x_vals[0]+self_occ_spc_x_vals[1]));
                result.setY(row);
                deciding = false;
            }
            else if(foe_row_count == 2){
                result.setX(gameboard->getBoardWidth()-(foe_occ_spc_x_vals[0]+foe_occ_spc_x_vals[1]));
                result.setY(row);
                deciding = false;
            }
        }
    }

    return result;
}

bool CpuPlayer::isCpu(){
    return true;
}