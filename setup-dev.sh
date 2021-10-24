#!/bin/bash
if ! command -v wget &> /dev/null
then
    echo "'wget' could not be found, please install"
    exit
fi

if ! command -v dialog &> /dev/null
then
    echo "'dialog' could not be found, please install"
    exit
fi

if ! command -v 7z &> /dev/null
then
    echo "'7z' could not be found, please install"
    exit
fi

if ! command -v cmake &> /dev/null
then
    echo "'cmake' could not be found, please install"
    exit
fi

if ! command -v git &> /dev/null
then
    echo "'git' could not be found, please install"
    exit
fi

if ! command -v make &> /dev/null
then
    echo "'make' could not be found, please install"
    exit
fi

cmd=(dialog --keep-tite --menu "Setup Cinder for development. Please, select OS:" 22 76 16)

options=(1 "macOS ARM"
         2 "Linux"
         3 "Windows")

choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

for choice in $choices
do
    case $choice in
        1)
            if ! command -v brew &> /dev/null
            then
                echo "'brew' could not be found, please install"
                exit
            fi
            brew install libomp 
            printf "\n\n\nReady"
            ;;
        2)
            echo "Not implemented"
            ;;
        3)
            echo "Not implemented"
            ;;
        4)

    esac
done
