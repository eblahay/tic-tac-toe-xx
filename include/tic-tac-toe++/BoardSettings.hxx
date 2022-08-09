#pragma once

#include <array>

struct BoardSettings{
    bool
        singleplayer = false,
        axis_labels = true
    ;

    int difficulty = 0;

    std::array<char, 3> marks = {' ','X','O'};
    std::array<char, 3> axis_nums = {'1', '2', '3'};
};