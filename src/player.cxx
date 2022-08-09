#include <tic-tac-toe++/player.hxx>

#include <exception>
#include <stdlib.h>

#include <tic-tac-toe++/Gameboard.hxx>
#include <tic-tac-toe++/ui.hxx>

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
    return txx::getCoord();
}

bool HumanPlayer::isCpu(){
    return false;
}

//CpuPlayerEasy

CpuPlayerEasy::CpuPlayerEasy(Gameboard* gameboard): PlayerBase::PlayerBase(gameboard){
    
}

Coord CpuPlayerEasy::pickDesCoord(){

    Coord result(rand() % gameboard->getBoardWidth(), rand() % gameboard->getBoardHeight());

    return result;
}

bool CpuPlayerEasy::isCpu(){
    return true;
}

//CpuPlayerHard

CpuPlayerHard::CpuPlayerHard(Gameboard* gameboard): PlayerBase::PlayerBase(gameboard){
    
}

Coord CpuPlayerHard::pickDesCoord(){

    Coord result(rand() % gameboard->getBoardWidth(), rand() % gameboard->getBoardHeight());


    bool deciding = true;

    //right-diag win condition check
    if(
        gameboard->getMark(0,2) == gameboard->getMark(1,1)
    ){
        if(gameboard->getMark(1,1) != gameboard->MARKS[0] && gameboard->getMark(2,0) == gameboard->MARKS[0]){
            result.copy({2,0});

            deciding = false;
        }
    }
    else if(
        gameboard->getMark(1,1) == gameboard->getMark(2,0)
    ){
        if(gameboard->getMark(1,1) != gameboard->MARKS[0] && gameboard->getMark(0,2) == gameboard->MARKS[0]){
            result.copy({0,2});

            deciding = false;
        }
    }
    else if(
        gameboard->getMark(0,2) == gameboard->getMark(2,0)
    ){
        if(gameboard->getMark(0,2) != gameboard->MARKS[0] && gameboard->getMark(1,1) == gameboard->MARKS[0]){
            result.copy({1,1});

            deciding = false;
        }
    }
    //left-diag win condition check
    if(deciding){
        if(
            gameboard->getMark(0,0) == gameboard->getMark(1,1)
        ){
            if(gameboard->getMark(1,1) != gameboard->MARKS[0] && gameboard->getMark(2,2) == gameboard->MARKS[0]){
                result.copy({2,2});

                deciding = false;
            }
        }
        else if(
            gameboard->getMark(1,1) == gameboard->getMark(2,2)
        ){
            if(gameboard->getMark(1,1) != gameboard->MARKS[0] && gameboard->getMark(0,0) == gameboard->MARKS[0]){
                result.copy({0,0});

                deciding = false;
            }
        }
        else if(
            gameboard->getMark(0,0) == gameboard->getMark(2,2)
        ){
            if(gameboard->getMark(0,0) != gameboard->MARKS[0] && gameboard->getMark(1,1) == gameboard->MARKS[0]){
                result.copy({1,1});

                deciding = false;
            }
        }

        for(int row=0; deciding && row < gameboard->getBoardHeight(); row++){
            int
                self_row_mark_count = 0,
                self_row_mark_cols[2] = {-1, -1},

                foe_row_mark_count = 0,
                foe_row_mark_cols[2] = {-1, -1}
            ;

            for(int collumn = 0; collumn < gameboard->getBoardWidth(); collumn++){
                if(gameboard->getMark(collumn, row) == this->getMark()){
                    self_row_mark_cols[self_row_mark_count] = collumn;
                    self_row_mark_count++;
                }
                else if(gameboard->getMark(collumn, row) != gameboard->MARKS[0]){
                    foe_row_mark_cols[foe_row_mark_count] = collumn;
                    foe_row_mark_count++;
                }
            }

            if(self_row_mark_count + foe_row_mark_count < gameboard->getBoardWidth()){
                if(self_row_mark_count == gameboard->getBoardWidth() - 1){
                    result.setX(gameboard->getBoardWidth() - (self_row_mark_cols[0] + self_row_mark_cols[1]));
                    result.setY(row);

                    deciding = false;
                }
                else if(foe_row_mark_count == gameboard->getBoardWidth() - 1){
                    result.setX(gameboard->getBoardWidth() - (foe_row_mark_cols[0] + foe_row_mark_cols[1]));
                    result.setY(row);

                    deciding = false;
                }
            }
            
        }

        for(int col=0; deciding && col < gameboard->getBoardHeight(); col++){
            int
                self_col_mark_count = 0,
                self_col_mark_cols[2] = {-1, -1},

                foe_col_mark_count = 0,
                foe_col_mark_cols[2] = {-1, -1}
            ;

            for(int row = 0; row < gameboard->getBoardWidth(); row++){
                if(gameboard->getMark(col, row) == this->getMark()){
                    self_col_mark_cols[self_col_mark_count] = row;
                    self_col_mark_count++;
                }
                else if(gameboard->getMark(col, row) != gameboard->MARKS[0]){
                    foe_col_mark_cols[foe_col_mark_count] = row;
                    foe_col_mark_count++;
                }
            }

            if(self_col_mark_count + foe_col_mark_count < gameboard->getBoardWidth()){
                if(self_col_mark_count == gameboard->getBoardWidth() - 1){
                    result.setY(gameboard->getBoardHeight() - (self_col_mark_cols[0] + self_col_mark_cols[1]));
                    result.setX(col);

                    deciding = false;
                }
                else if(foe_col_mark_count == gameboard->getBoardWidth() - 1){
                    result.setY(gameboard->getBoardHeight() - (foe_col_mark_cols[0] + foe_col_mark_cols[1]));
                    result.setX(col);

                    deciding = false;
                }
            }
            
        }

    }

    return result;
}

bool CpuPlayerHard::isCpu(){
    return true;
}