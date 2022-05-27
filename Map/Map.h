#pragma once

#include <cstdint>
#include <cstddef>

#include "Enums.h"

namespace Cinder {

struct River {
    TileBorder riverEntry;
    TileBorder riverExit;
};

#pragma pack(push, 1)
struct BiomeCell {
    Biomes tile: 5;
    RiverDirection river: 3;
};
#pragma pack(pop)

static_assert(sizeof(BiomeCell) == sizeof(uint8_t), "BiomeCell and uint8_t sizes mismatch");

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

