#pragma once

#include <cstdint>

#include "stable_random.h"

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

enum class TileBorder {
    NONE = 0,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

struct River {
    TileBorder riverEntry;
    TileBorder riverExit;
};

enum class MapTypes {
    WORLD_MAP,
    CELL_MAP
};

struct MapConfig {
    uint64_t seed;
    uint32_t width  = 512;
    uint32_t height = 512;
    float sea_level = 0;
    float high_rock_level = 0.35;
    float rock_level = 0.25;
    float wet_equator = 0.5;
    float river_density = 0.1;
};

struct Map {
    MapTypes mapType;
    uint32_t width;
    uint32_t height;
    uint8_t * map;
    River *rivers;
    Random rand;

    uint64_t seed;

    Map(const MapConfig &cfg);
    ~Map();

    float get_altitude(uint32_t x, uint32_t y);
    void generate_river_starting_from(uint32_t x, uint32_t y);

    void save_to_file(const char *filename);
    void load_from_file(const char *filename);
};

}; // namespace Cinder

