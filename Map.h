#pragma once

#include <cstdint>

#include "constants.h"

namespace Cinder {

struct River {
    TileBorder riverEntry;
    TileBorder riverExit;
};

class MapColumn {
public:
    MapColumn(BiomeCell *_base);
    BiomeCell& operator[](const size_t row);
private:
    BiomeCell *base;
};

struct Map {
    uint32_t width;
    uint32_t height;
    MapTypes mapType = MapTypes::WORLD_MAP;
    BiomeCell *map;
    MapColumn operator[](const size_t column);
    River *rivers;
    void save_to_file(const char *filename);
};

}; // namespace Cinder

