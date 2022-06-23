#pragma once

#include <cstdint>
#include <memory>

#include "stable_random.h"
#include "Map.h"

namespace Cinder {

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
    River *rivers;
    Random rand;

    float get_altitude(uint32_t x, uint32_t y);
    void generate_river_starting_from(uint32_t x, uint32_t y);

    std::shared_ptr<Map> generate_map();
};

}; // namespace Cinder

