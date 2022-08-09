#pragma once

#include <vector>
#include <array>
#include <memory>

#include <tic-tac-toe++/Coord.hxx>
#include <tic-tac-toe++/player.hxx>

#include <tic-tac-toe++/BoardSettings.hxx>

class Gameboard{
    public:
        Gameboard(BoardSettings settings);

        void changeTurn();

        void claimSpace(Coord position, int claimant);

        void handleTurn();

        int findWinner();

        //functions that set the value(s) of class members
        void setMark(Coord position, char mark);

        //functions that return objects
        char getMark(Coord position) const ;
        char getMark(int x, int y) const ;

        int getBoardWidth() const ;
        int getBoardHeight() const ;

        Coord getLatestMove() const ;

        const int& getTurnHolderIndex() const ;

        int getPriorTurnHolderIndex() const ;

        int getCurrentTurn() const ;

        const bool& axisLabels() const ;

        //public non-function class members
        const BoardSettings SETTINGS;
        const std::array<char, 3> MARKS;
        constexpr static int
            UNDECIDED = -1,
            STALEMATE = -2
        ;
    private:
        const int BOARD_WIDTH, BOARD_HEIGHT;
        const bool SINGLEPLAYER, AXIS_LABELS;

        Coord latest_move;

        std::vector<std::vector<char>> board;
        std::vector<std::unique_ptr<PlayerBase>> players;

        int turn=0, turn_holder_index=0;
};