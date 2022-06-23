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
    MapTypes mapType = MapTypes::WORLD_MAP;
    uint32_t width = 0;
    uint32_t height = 0;

    MapColumn operator[](const size_t column);

    bool loadFromFile(const std::string &filename);
    void saveToFile(const std::string &filename);

private:
    friend class MapGenerator;
    BiomeCell *map = nullptr;
};

}; // namespace Cinder

