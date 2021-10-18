#include <cstdio>

#include "map.h"
#include "perlin_noise.h"

namespace Cinder {

Map::Map(uint32_t _width, uint32_t _height, uint64_t seed) :
    width(_width),
    height(_height),
    map(new uint8_t[width * height]),
    mapType(MapTypes::WORLD_MAP)
{
    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            float temperature = perlin(seed + 0.03 * x + 0.5, seed + 0.03 * y + 0.5);
            float moisture    = perlin(seed + 5000 + 0.02 * x + 0.111, seed + 5000 + 0.02 * y + 0.1111);
            float altitude    = 0.25 * (
                perlin(seed + 100000 + 0.1 * x + 0.111, seed + 10000 + 0.1 * y + 0.1111) +
                perlin(seed + 200000 + 0.01 * x + 0.111, seed + 20000 + 0.01 * y + 0.1111) +
                perlin(seed + 300000 + 0.005 * x + 0.111, seed + 30000 + 0.005 * y + 0.1111) +
                perlin(seed + 400000 + 0.001 * x + 0.111, seed + 40000 + 0.001 * y + 0.1111)
            );

            Biomes biom = altitude < 0 ? temperature > -0.3 ? Biomes::WATER : Biomes::GLACIER
                        : altitude > 0.35 ? Biomes::HIGH_ROCK
                        : altitude > 0.25 ? Biomes::ROCK
                        : moisture > 0.3 ? Biomes::SWAMP
                        : moisture > 0.1 ? Biomes::FOREST
                        : moisture > -0.1 ? Biomes::FIELD
                        : moisture > -0.2 ? Biomes::SAVANNA
                        : Biomes::DESERT;

            map[x * height + y] = static_cast<uint8_t>(biom);
        }
    }
}

Map::~Map() {
    delete[] map;
}

void Map::save_to_file(const char *filename) {
    FILE *f;
    f = fopen(filename, "wb");
    if (!f) {
        return;
    }
    uint32_t _mapType = (uint32_t)mapType;
    fwrite(&_mapType, sizeof(uint32_t), 1, f);
    fwrite(&height, sizeof(uint32_t), 1, f);
    fwrite(&width, sizeof(uint32_t), 1, f);
    fwrite(map, sizeof(uint8_t), width * height, f);
}

// TODO: replace with a reliable implementation
// When reading 512x512 it skips last 12 tiles of the map
void Map::load_from_file(const char *filename) {
    delete[] map;

    FILE *f;
    f = fopen(filename, "rb");
    if (!f) {
        return;
    }
    uint32_t _mapType;
    fread(&_mapType, sizeof(uint32_t), 1, f);
    fread(&height, sizeof(uint32_t), 1, f);
    fread(&width, sizeof(uint32_t), 1, f);

    map = new uint8_t[width * height];
    fread(map, sizeof(uint8_t), width * height, f);
}

}; // namespace Cinder
