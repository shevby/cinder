#pragma once

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

struct MapConfig {
    uint64_t seed;
    uint32_t width  = 512;
    uint32_t height = 512;
    float sea_level = 0;
    float high_rock_level = 0.35;
    float rock_level = 0.25;
};

struct Map {
    MapTypes mapType;
    uint32_t width;
    uint32_t height;
    uint8_t * map;

    Map(const MapConfig &cfg);
    ~Map();

    void save_to_file(const char *filename);
    void load_from_file(const char *filename);
};

}; // namespace Cinder

