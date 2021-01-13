#!/bin/bash

NEWLINE="
"
EMPTY_CHAR="..."


declare \
PROJECT_NAME \
VERSION_NUMBER \
STAGE \
LATEST_RELEASE \
LATEST_BIN \
STAGE_SYMBOL \
BINARY_NAME \
BINARY_DIR \
SRC_DIR \
RELEASE_DIR \
CPP_STD

function init {
    CONFIG_FILE="proj.config"
    IFS_BAK="$IFS"
    IFS="$NEWLINE"
    ver_info=(`cat "$CONFIG_FILE"`)
    IFS="$IFS_BAK"

    VERSION_NUMBER="${ver_info[0]}"
    STAGE="${ver_info[1]}"
    LATEST_RELEASE="${ver_info[2]}"
    LATEST_BIN="${ver_info[3]}"
    PROJECT_NAME="${ver_info[4]}"
    CPP_STD="${ver_info[5]}"


    if [[ "$STAGE" == "pre-alpha" ]]; then
        STAGE_SYMBOL="p_α"
    elif [[ "$STAGE" == "alpha" ]]; then
        STAGE_SYMBOL="α"
    elif [[ "$STAGE" == "beta" ]]; then
        STAGE_SYMBOL="β"
    elif [[ "$STAGE" == "gamma" || "$STAGE" == "release" ]]; then
        STAGE_SYMBOL=""
    else
        printf "\033[31;1merror:\033[0m unknown stage in proj_ver file.\n\033[1mOverwrite proj_ver file?\033[0m\n(Y/n) "
        read yn
        if [[ "${yn,}" == "y" ]]; then
            wipeConfig
        else
            printf "unable to proceed; terminating program.\n"
            exit 1
        fi
    fi

    BINARY_NAME=$PROJECT_NAME"_"$VERSION_NUMBER
    BINARY_DIR="bin/"
    SRC_DIR="src/"
    RELEASE_DIR="bin/release/"
}

function wipeConfig {
    printf "0.0.0""\n" > "$CONFIG_FILE"
    printf "pre-alpha\n" >> "$CONFIG_FILE"
    printf "$EMPTY_CHAR\n" >> "$CONFIG_FILE"
    printf "$EMPTY_CHAR\n" >> "$CONFIG_FILE"
    printf "C++ Project\n" >> "$CONFIG_FILE"
    printf "c++14" >> "$CONFIG_FILE"

    #re-initializing in-program variables so they match those in the file
    init
}

function printHelpMenu {
    MENU_TEXT="
                          Project Script Help Menu
-------------------------------------------------------------------------------
--help            ....prints this menu
--compile       ....compiles the project source code into a new binary executable
                    ( currently '"$BINARY_NAME"' )
--release       ....compiles a new release binary
--proj_info    ....displays information about the project
--set_version <VERSION>    ....sets the current project version to <VERSION>
--set_stage <STAGE>        ....sets the current stage of the project's life cycle to <STAGE>
    valid stages:
        pre-alpha
        alpha
        beta
        gamma, release
--set_cpp_std <STD>        ....sets the c++ standard for the project to <STD>
--wipe_config              ....overwrites the project config file with default values
"

    echo "$MENU_TEXT"
}

function updateConfig {
    printf "$VERSION_NUMBER""\n" > "$CONFIG_FILE"
    printf "$STAGE""\n" >> "$CONFIG_FILE"
    printf "$LATEST_RELEASE""\n" >> "$CONFIG_FILE"
    printf "$LATEST_BIN""\n" >> "$CONFIG_FILE"
    printf "$PROJECT_NAME""\n" >> "$CONFIG_FILE"
    printf "$CPP_STD" >> "$CONFIG_FILE"

    #re-initializing in-program variables so they match those in the config
    init
}

#main method
init

for (( i=1; i<=$#; i++)) do
    arg=${!i}

    j=$((i+1))

    if [[ "$arg" == "--help" ]]; then
        printHelpMenu

        break
    elif [[ "$arg" == "--compile" ]]; then
        if [[ "$VERSION_NUMBER" == "$EMPTY_CHAR" ]]; then
            printf "\033[31;1merror:\033[0m unknown version number.\n  type '--help' for help.\n"
            exit 1
        fi
        echo "Compiling"
        g++ -std=$CPP_STD -o "$BINARY_DIR$BINARY_NAME" "$SRC_DIR"*.cpp

        LATEST_BIN="$BINARY_DIR$BINARY_NAME"

        updateConfig

        break
    elif [[ "$arg" == "--proj_info" ]]; then
        echo "Project Name: ""$PROJECT_NAME"
        echo "Semantic Version: ""$VERSION_NUMBER"
        echo "Stage of Life: ""$STAGE_SYMBOL"" ("$STAGE")"
        echo "Latest Release: ""$LATEST_RELEASE"
        echo "Latest Binary: ""$LATEST_BIN"
        echo "C++ Standard: ""$CPP_STD"

        break
    elif [[ "$arg" == "--wipe_config" ]]; then
        wipeConfig
    elif [[ "$arg" == "--set_version" ]]; then
        VERSION_NUMBER="${!j}"

        updateConfig

        ((i++))
    elif [[ "$arg" == "--set_stage" ]]; then
        stage="${!j}"
        if [[ "${!j}" == "pre-alpha" || "${!j}" == "alpha" || "${!j}" == "beta" || "${!j}" == "gamma" || "${!j}" == "release" ]]; then
            :
        else
            printf "\033[31;1merror:\033[0m unknown version number.\n  type '--help' for help.\n"
            break
        fi

        STAGE="$stage"

        updateConfig

        ((i++))
    elif [[ "$arg" == "--set_name" ]]; then
        PROJECT_NAME="${!j}"

        updateConfig

        ((i++))
    elif [[ "$arg" == "--release" ]]; then
        printf "Are sure you want to compile the existing source code into a new release?\n\033[1m[SOURCE] -> g++ -> \"""$RELEASE_DIR""$BINARY_NAME""$STAGE""\"\033[0m\n(Y/n) "
        read yn
        if [[ "${yn,}" == "y" ]]; then
            if [[ "${LATEST_RELEASE}" == "$VERSION_NUMBER" ]]; then
                printf "\033[31;1merror:\033[0m There is an existing release with the current version number.\nplease update the current version number and try again.\n"
            elif [[ "$STAGE" == "$EMPTY_CHAR" || $LATEST_BIN == "$EMPTY_CHAR" ]]; then
                printf "\033[31;1merror:\033[0m one or more fields in proj_ver are blank.\n\033[31mRelease aborted.\033[0m\n"
            else
                printf "Creating new release"

                g++ -std="$CPP_STD" -o "$RELEASE_DIR""$BINARY_NAME""$STAGE_SYMBOL" "$SRC_DIR"*.cpp

                LATEST_RELEASE="$VERSION_NUMBER"

                updateConfig

            fi
        else
            printf "\033[31mRelease aborted.\033[0m\n"
        fi

        break
    elif [[ "$arg" == "--set_cpp_std" ]]; then
        CPP_STD="${!j}"

        updateConfig

        ((i++))
    else
        printf "\033[31;1merror:\033[0m unknown argument\n  type '--help' for help.\n"

        break
    fi
done
exit 0