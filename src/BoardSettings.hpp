#ifndef BOARD_SETTINGS_HPP
#define BOARD_SETTINGS_HPP

#include <vector>

struct BoardSettings{
    bool singleplayer = false;

    int difficulty = 0;

    std::vector<char> theme = {'_','X','O'};
};

#endif