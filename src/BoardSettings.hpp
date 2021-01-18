#ifndef BOARD_SETTINGS_HPP
#define BOARD_SETTINGS_HPP

#include <vector>

struct BoardSettings{
    bool
        singleplayer = false,
        axis_labels = true
    ;

    int difficulty = 0;

    std::vector<char> theme = {'_','X','O'};
};

#endif