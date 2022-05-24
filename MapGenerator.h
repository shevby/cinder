#pragma once

#include <cstdint>

#include "constants.h"
#include "stable_random.h"

namespace Cinder {

struct River {
    TileBorder riverEntry;
    TileBorder riverExit;
};

struct MapGenerator {
    uint64_t seed;
    uint32_t width  = 512;
    uint32_t height = 512;
    float sea_level = 0;
    float high_rock_level = 0.35;
    float rock_level = 0.25;
    float wet_equator = 0.5;
    float river_density = 0.1;

    MapTypes mapType = MapTypes::WORLD_MAP;
    BiomeCell *map;
    BiomeCell& map_at(size_t x, size_t y);
    River *rivers;
    Random rand;

    float get_altitude(uint32_t x, uint32_t y);
    void generate_river_starting_from(uint32_t x, uint32_t y);

    void generate_map();
    void save_to_file(const char *filename);
};

}; // namespace Cinder

