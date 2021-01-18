#include "Gameboard.hpp"

Gameboard::Gameboard(BoardSettings settings):
    BOARD_WIDTH(3),
    BOARD_HEIGHT(3),
    SINGLEPLAYER(settings.singleplayer),
    AXIS_LABELS(settings.axis_labels),
    MARKS(settings.theme)
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
    int human_player_qty = 2, cpu_player_qty=0;
    if(settings.singleplayer){
        human_player_qty = 1;
        cpu_player_qty = 1;
    }

    for(int i=0; i < human_player_qty; i++){
        players.push_back(std::make_unique<HumanPlayer>(this));
        players[i]->setMark(MARKS[i+1]);
    }
    for(int i=human_player_qty; i < human_player_qty+cpu_player_qty; i++){
        if(settings.difficulty == 1) players.push_back(std::make_unique<CpuPlayerHard>(this));
        else players.push_back(std::make_unique<CpuPlayerEasy>(this));
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

    latest_move = position;
}

void Gameboard::drawBoard(){
    /*
    a function that draws the board on the screen.
    */

    std::cout << "It's Player " << turn_holder_index + 1 << "'s turn!\n";

    for(int row=0; row<BOARD_HEIGHT; row++){
        if(AXIS_LABELS) std::cout << BOARD_HEIGHT-row << " ";
        for(int width=0; width<BOARD_WIDTH; width++){
            std::cout << getMark(width, row);
            if(AXIS_LABELS && width != BOARD_WIDTH - 1){
                std::cout << "|";
            }
        }
        std::cout << '\n';
    }
    if(AXIS_LABELS) std::cout << "  ";
    for(int width=0; AXIS_LABELS && width<BOARD_WIDTH; width++){
        std::cout << width + 1 << ' ';
    }
    if(AXIS_LABELS) std::cout << '\n';
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
            std::cout << "Type input in this form: 'x,y'\n";
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
        winner_index = Gameboard::UNDECIDED// -1 = no_current_winner, -2 = stalemate
    ;    

    //right-diag win condition check
    if(this->getMark(0,2) == this->getMark(1,1) && this->getMark(1,1) == this->getMark(2,0) && this->getMark(1,1) == players[getPriorTurnHolderIndex()]->getMark()) winner_index = getPriorTurnHolderIndex();
    //left-diag win condition check
    else if(this->getMark(0,0) == this->getMark(1,1) && this->getMark(1,1) == this->getMark(2,2) && this->getMark(1,1) == players[getPriorTurnHolderIndex()]->getMark()) winner_index = getPriorTurnHolderIndex();

    int row = latest_move.y(), collumn = latest_move.x();
    //horizontal row win condition check
    if(this->getMark(0,row) == this->getMark(1,row) && this->getMark(1,row) == this->getMark(2,row) && this->getMark(0,row) == players[getPriorTurnHolderIndex()]->getMark()) winner_index = getPriorTurnHolderIndex();

    //vertical collumn win condition check
    if(this->getMark(collumn,0) == this->getMark(collumn,1) && this->getMark(collumn,1) == this->getMark(collumn,2) && this->getMark(collumn,0) == players[getPriorTurnHolderIndex()]->getMark()) winner_index = getPriorTurnHolderIndex();  

    //if a winner hasn't decided, but it's the last possible turn, call a stalemate
    if(winner_index == Gameboard::UNDECIDED && getCurrentTurn() > 8) winner_index = Gameboard::STALEMATE;


    return winner_index;
}

void Gameboard::setMark(Coord position, char mark){
    board[position.y()][position.x()] = mark;
}

char Gameboard::getMark(Coord position) const {
    return board[position.y()][position.x()];
}
char Gameboard::getMark(int x, int y) const {
    return board[y][x];
}

int Gameboard::getBoardWidth() const {
    return BOARD_WIDTH;
}
int Gameboard::getBoardHeight() const {
    return BOARD_HEIGHT;
}

Coord Gameboard::getLatestMove() const {
    return latest_move;
}

int Gameboard::getPriorTurnHolderIndex() const {
    int result = turn_holder_index - 1;

    if(result < 0) result = players.size() - 1;

    return result;
}

int Gameboard::getCurrentTurn() const {
    return turn;
}