#include <ncurses.h>
#include <iostream>

#include "../MapGenerator.h"
#include "MapViewer.h"

using namespace Cinder;

int main() {
    initscr();

    srand(time(NULL));

    MapGenerator mapgen;
    mapgen.seed = rand() * 10000000;
    mapgen.width = 200;
    mapgen.height = 200;
    mapgen.generate_map();

    MapViewer view(mapgen);
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