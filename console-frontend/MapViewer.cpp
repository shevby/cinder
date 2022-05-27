#include <ncurses.h>
#include <unordered_map>

#include "MapViewer.h"

namespace Cinder {

/**********************************************************
 *              Color initialization section              *
 **********************************************************/

// `ncurses` library uses color pairs in order to use
// colors in the console.

struct BiomeInfo {
    char ch;        // character to display
    int color_pair; // ncurses color pair
    int color;      // ncurses text color
    int bgColor;    // ncurses background color
};

static std::unordered_map<Biomes, BiomeInfo> biomesInfo = {
    {Biomes::WATER,     {'~', 100, COLOR_WHITE, COLOR_BLUE}},
    {Biomes::FIELD,     {'F', 101, COLOR_BLACK, COLOR_YELLOW}},
    {Biomes::FOREST,    {'^', 102, COLOR_BLACK, COLOR_GREEN}},
    {Biomes::ROCK,      {'r', 103, COLOR_WHITE, COLOR_BLACK}},
    {Biomes::HIGH_ROCK, {'R', 104, COLOR_WHITE, COLOR_BLACK}},
    {Biomes::GLACIER,   {'G', 105, COLOR_WHITE, COLOR_BLUE}},
    {Biomes::SWAMP,     {'S', 106, COLOR_BLACK, COLOR_GREEN}},
    {Biomes::DESERT,    {'D', 107, COLOR_BLACK, COLOR_YELLOW}},
    {Biomes::SAVANNA,   {'S', 108, COLOR_BLACK, COLOR_YELLOW}},
};

constexpr int ERROR_COLOR_PAIR      = 150;
constexpr int OUT_OF_MAP_COLOR_PAIR = 151;

void MapViewer::initColors() {
    start_color();

    for (const auto& pair : biomesInfo) {
        const auto& info = pair.second;
        init_pair(info.color_pair, info.color, info.bgColor);
    }

    init_pair(ERROR_COLOR_PAIR,      COLOR_BLACK, COLOR_RED);
    init_pair(OUT_OF_MAP_COLOR_PAIR, COLOR_BLACK, COLOR_BLACK);
}

/**********************************************************
 *          End of color initialization section           *
 **********************************************************/

MapViewer::MapViewer(std::shared_ptr<Map> _map) : map(_map), x(0), y(0) {}

static void draw_char_with_color(char ch, int color_pair) {
    attron(COLOR_PAIR(color_pair));
    addch(ch);
    attroff(COLOR_PAIR(color_pair));
}

void MapViewer::draw() {
    for (int y_offset=0; y_offset<LINES; ++y_offset) {
        for (int x_offset=0; x_offset<COLS; ++x_offset) {
            move(y_offset, x_offset);
            int map_x = x + x_offset;
            int map_y = y + y_offset;
            bool out_of_bounds = (map_x < 0) || (map_y < 0) || (map_x >= map->width) || (map_y >= map->height);
            if (out_of_bounds) {
                draw_char_with_color(' ', OUT_OF_MAP_COLOR_PAIR);
                continue;
            }
            auto m = *map;
            auto biome = m[map_x][map_y].tile;
            auto info = biomesInfo.find(biome);
            if (info == biomesInfo.end()) {
                draw_char_with_color('?', ERROR_COLOR_PAIR);
            }
            else {
                draw_char_with_color(info->second.ch, info->second.color_pair);
            }
        }
    }
}

} // namespace Cinder
