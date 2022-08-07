#pragma once

#include <vector>

struct BoardSettings{
    bool
        singleplayer = false,
        axis_labels = true
    ;

    int difficulty = 0;

    std::vector<char> theme = {'_','X','O'};
};