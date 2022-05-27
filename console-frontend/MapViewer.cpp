#include <ncurses.h>

#include "Character.h"
#include "MapViewer.h"

namespace Cinder {

MapViewer::MapViewer(std::shared_ptr<Map> _map) : map(_map), x(0), y(0) {}

Character biomeToChar(BiomeCell biome) {
    switch(biome.tile) {
    case Biomes::WATER: return {'~', Character::Color::White, Character::Color::Blue};
    case Biomes::FIELD: return {'F', Character::Color::Black, Character::Color::Yellow};
    case Biomes::FOREST: return {'^', Character::Color::Black, Character::Color::Green};
    case Biomes::ROCK: return {'r', Character::Color::White, Character::Color::Black};
    case Biomes::HIGH_ROCK: return {'R', Character::Color::White, Character::Color::Black};
    case Biomes::GLACIER: return {'G', Character::Color::White, Character::Color::Blue};
    case Biomes::SWAMP: return {'S', Character::Color::Black, Character::Color::Green};
    case Biomes::DESERT: return {'D', Character::Color::Black, Character::Color::Yellow};
    case Biomes::SAVANNA: return {'S', Character::Color::Black, Character::Color::Yellow};
    default: return {'?', Character::Color::Black, Character::Color::Red};
    }
}

void MapViewer::draw() {
    for (int y_offset=0; y_offset<LINES; ++y_offset) {
        for (int x_offset=0; x_offset<COLS; ++x_offset) {
            move(y_offset, x_offset);
            int map_x = x + x_offset;
            int map_y = y + y_offset;
            bool out_of_bounds = (map_x < 0) || (map_y < 0) || (map_x >= map->width) || (map_y >= map->height);
            if (out_of_bounds) {
                Character ch(' ');
                ch.display();
                continue;
            }
            auto m = *map;
            Character ch = biomeToChar(m[map_x][map_y]);
            ch.display();
        }
    }
}

} // namespace Cinder
