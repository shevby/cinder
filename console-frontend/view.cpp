#include <ncurses.h>
#include <iostream>

#include "MapGenerator/MapGenerator.h"
#include "MapViewer.h"

using namespace Cinder;

int main() {
    initscr();
    MapViewer::initColors();

    srand(time(NULL));

    MapGenerator mapgen;
    mapgen.seed = rand() * 10000000;
    mapgen.width = 200;
    mapgen.height = 200;

    MapViewer view(mapgen.generate_map());
    view.draw();

    int ch;
    while (ch = getch()) {
        if (ch == 'q') break;
        if (ch == 'w') view.y--;
        if (ch == 's') view.y++;
        if (ch == 'a') view.x--;
        if (ch == 'd') view.x++;
        view.draw();
    }

    endwin();
}
