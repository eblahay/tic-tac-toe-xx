cmake_minimum_required(VERSION 3.22)

# set project name
project(Tic-Tac-Toe++)

# add executable
set(SOURCES 
    src/main.cxx
    src/Coord.cxx
    src/Gameboard.cxx
    src/player.cxx
    src/validators.cxx
)
add_executable(tic-tac-toe-xx ${SOURCES})


# include directories must come AFTER the executable's been added
include_directories(include)


# specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)