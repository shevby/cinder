#ifndef _CINDER_MAP_H_
#define _CINDER_MAP_H_

#include <cstdint>

namespace Cinder {

enum class Biomes {
    WATER = 0,
    FIELD,
    FOREST,
    ROCK,
    HIGH_ROCK,
    GLACIER,
    SWAMP,
    DESERT,
    SAVANNA,
};

enum class MapTypes {
    WORLD_MAP,
    CELL_MAP
};

struct Map {
    MapTypes mapType;
    uint32_t width;
    uint32_t height;
    uint8_t * map;
};

}; // namespace Cinder

#endif // ifndef _CINDER_MAP_H_
