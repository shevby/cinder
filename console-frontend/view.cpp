#include <cstdlib>
#include <ncurses.h>
#include <string>

#include "MapGenerator/MapGenerator.h"
#include "MapViewer.h"

using namespace Cinder;

int main(int argc, char **argv) {
    initscr();
    MapViewer::initColors();

    srand(time(NULL));

    std::shared_ptr<Map> map = std::make_shared<Map>();

    if (argc > 1) {
        map->loadFromFile(argv[1]);
    }
    else {
        MapGenerator mapgen;
        mapgen.seed = rand() / 1000;
        mapgen.width = 200;
        mapgen.height = 200;

        map = mapgen.generate_map();
    }

    MapViewer view(map);
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
