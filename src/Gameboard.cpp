#include "Gameboard.hpp"

Gameboard::Gameboard(std::vector<char> theme):
    BOARD_WIDTH(3),
    BOARD_HEIGHT(3),
    MARKS(theme)
{
    //intialize board
    for(int row_i=0; row_i<BOARD_HEIGHT; row_i++){
        std::vector<char> row;
        for(int collumn_i=0; collumn_i<BOARD_WIDTH; collumn_i++){
            row.push_back(MARKS[0]);
        }
        board.push_back(row);
    }

    //load players
    for(int i=0; i < 2; i++){
        players.push_back(std::make_unique<HumanPlayer>(this));
        players[i]->setMark(MARKS[i+1]);
    }

}

void Gameboard::changeTurn(){
    turn++;
    if(turn_holder_index + 1 >= players.size()) turn_holder_index = 0;
    else turn_holder_index++;
}

void Gameboard::claimSpace(Coord position, int claimant){
    setMark(position, players[claimant]->getMark());
}

void Gameboard::drawBoard(){
    /*
    a function that draws the board on the screen.
    */

    std::cout << "It's Player " << turn_holder_index + 1 << "'s turn!\n";

    for(int row=0; row<BOARD_HEIGHT; row++){
        for(int width=0; width<BOARD_WIDTH; width++){
            std::cout << getMark(width, row);
        }
        std::cout << '\n';
    }
}

void Gameboard::handleTurn(){
    Coord new_claim;

    do{
        try{
            new_claim = players[turn_holder_index]->pickDesCoord();
        }
        catch(std::runtime_error err){
            new_claim.setX(-1);
            new_claim.setY(-1);
        }
    }
    while(
        (new_claim.x() < 0 || new_claim.y() < 0) ||
        (new_claim.x() >= BOARD_WIDTH || new_claim.y() >= BOARD_HEIGHT) ||
        (getMark(new_claim) != MARKS[0])
    );

    claimSpace(new_claim, turn_holder_index);
    changeTurn();
}

int Gameboard::findWinner(){
    /*
    function that tries to find if any of the players have met the
    conditions necessary to win the game.
    */

    int
        winner_index = Gameboard::UNDECIDED,// -1 = no_current_winner, -2 = stalemate
        blank_space_count = 0
    ;    

    for(int player_index=0; player_index < players.size() && winner_index == Gameboard::UNDECIDED; player_index++){
        //right-diag win condition check
        if(this->getMark(0,2) == this->getMark(1,1) && this->getMark(1,1) == this->getMark(2,0) && this->getMark(1,1) == players[player_index]->getMark()) winner_index = player_index;
        //left-diag win condition check
        else if(this->getMark(0,0) == this->getMark(1,1) && this->getMark(1,1) == this->getMark(2,2) && this->getMark(1,1) == players[player_index]->getMark()) winner_index = player_index;

        //iterating through board
        for(int row=0; row < board.size() && winner_index == Gameboard::UNDECIDED ; row++){
            //horizontal row win condition check
            if(this->getMark(0,row) == this->getMark(1,row) && this->getMark(1,row) == this->getMark(2,row) && this->getMark(0,row) == players[player_index]->getMark()) winner_index = player_index;

            //iterating through board (collumns in row)
            for(int collumn=0; collumn < board[row].size() && winner_index == Gameboard::UNDECIDED; collumn++){
                //vertical collumn win condition check
                if(this->getMark(collumn,0) == this->getMark(collumn,1) && this->getMark(collumn,1) == this->getMark(collumn,2) && this->getMark(collumn,0) == players[player_index]->getMark()) winner_index = player_index;

                if(this->getMark(collumn,row) == MARKS[0]) blank_space_count++;
            }          
        }
    }
    if(winner_index == Gameboard::UNDECIDED && blank_space_count == 0) winner_index = Gameboard::STALEMATE;

    return winner_index;
}

void Gameboard::setMark(Coord position, char mark){
    board[position.y()][position.x()] = mark;
}

char Gameboard::getMark(Coord position){
    return board[position.y()][position.x()];
}
char Gameboard::getMark(int x, int y){
    return board[y][x];
}

int Gameboard::getBoardWidth() const {
    return BOARD_WIDTH;
}
int Gameboard::getBoardHeight() const {
    return BOARD_HEIGHT;
}