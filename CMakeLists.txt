cmake_minimum_required(VERSION 3.22)

# set project name
project(Tic-Tac-Toe++)

# add executable
set(SOURCES 
    src/main.cxx
    src/Coord.cxx
    src/Gameboard.cxx
    src/player.cxx
    src/ui.cxx
)
add_executable(tic-tac-toe-xx ${SOURCES})
target_link_libraries(tic-tac-toe-xx Boost::program_options ncurses)

find_package(Boost 1.74 COMPONENTS program_options REQUIRED)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

# include directories must come AFTER the executable's been added
#include_directories(include ${Boost_INCLUDE_DIR} ${CURSES_INCLUDE_DIRS})
include_directories(include)


# specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)