#!/bin/bash

VERSION_NUMBER="0.2.0"
PROJECT_NAME="Tic-Tac-Toe++"
VERSION_LETTER="α"
BINARY_NAME=$PROJECT_NAME"_"$VERSION_NUMBER
BINARY_DIR="bin/"

CPP_STANDARD="c++17"

function printHelpMenu {
    MENU_TEXT="
                    Project "$PROJECT_NAME" Help Menu
-------------------------------------------------------------------------------
-h            ....prints this menu
compile       ....compiles the project source code into a new binary executable
                    ( currently '"$BINARY_NAME"' )
exe           ....executes the current binary without any additional arguments
"

    echo "$MENU_TEXT"
}

for arg in $@; do
    if [[ "$arg" == "-h" ]]; then
        printHelpMenu
        exit 0
    elif [[ "$arg" == "compile" ]]; then
        echo "Compiling"
        g++ -std=$CPP_STANDARD -o $BINARY_DIR$BINARY_NAME src/*.cpp
    elif [ "$arg" == "exe" ]; then
        "./$BINARY_DIR$BINARY_NAME"
    fi
done
exit 0