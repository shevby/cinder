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

cmd=(dialog --keep-tite --menu "Building SFML. Please, select OS:" 22 76 16)

options=(1 "macOS ARM"
         2 "Linux"
         3 "Windows")

choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

for choice in $choices
do
    case $choice in
        1)
            git clone https://github.com/SFML/SFML
            git submodule init
            git submodule update
            cat imgui-sfml/imconfig-SFML.h >> imgui/imconfig.h
            cd SFML
            printf "set(CMAKE_OSX_ARCHITECTURES \"arm64\" CACHE STRING \"macOS architecture to build; 64-bit is expected\" FORCE)\n" > tmp.txt
            cat CMakeLists.txt >> tmp.txt
            mv tmp.txt CMakeLists.txt
            mkdir build
            cd build
            cmake ../
            make
            cd ../..
            mkdir bin
            mkdir bin/sfml
            mv -v SFML/build/lib bin/sfml
            mv -v SFML/include bin/sfml
            mv SFML/license.md bin/sfml
            cp -r SFML/extlibs/libs-osx/Frameworks bin/sfml/
            mv -v SFML/extlibs/libs-osx/Frameworks/* bin/sfml/lib
            rm -rfv SFML
            printf "\n\n\nSFML has been configured"
            ;;
        2)
            wget -O sfml.tar.gz https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-linux-gcc-64-bit.tar.gz
            7z x sfml.tar.gz
            rm sfml.tar.gz
            7z x sfml.tar
            rm sfml.tar
            mkdir bin
            mkdir bin/sfml
            mv -v SFML-2.5.1/* bin/sfml/
            rm -rfv SFML-2.5.1
            ;;
        3)
            wget -O sfml.tar.gz https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
            7z x sfml.tar.gz
            rm sfml.tar.gz
            7z x sfml.tar
            rm sfml.tar
            mkdir bin
            mkdir bin/sfml
            mv -v SFML-2.5.1/* bin/sfml/
            rm -rfv SFML-2.5.1
            ;;
        4)

    esac
done
