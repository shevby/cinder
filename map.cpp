#include <cstdio>
#include <vector>

#include "biom_generator.h"
#include "map.h"

namespace Cinder {

Map::Map(uint32_t _width, uint32_t _height, uint64_t _seed) :
    width(_width),
    height(_height),
    map(new uint8_t[width * height]),
    mapType(MapTypes::WORLD_MAP)
{
    std::vector<Cinder::Biomes> biomes;

    for (size_t i = 0; i < 5; ++i) {
        biomes.push_back(Cinder::Biomes::WATER);
        biomes.push_back(Cinder::Biomes::FIELD);
        biomes.push_back(Cinder::Biomes::FOREST);
        biomes.push_back(Cinder::Biomes::ROCK);
        biomes.push_back(Cinder::Biomes::HIGH_ROCK);
        biomes.push_back(Cinder::Biomes::GLACIER);
        biomes.push_back(Cinder::Biomes::SWAMP);
        biomes.push_back(Cinder::Biomes::DESERT);
        biomes.push_back(Cinder::Biomes::SAVANNA);
    }

    auto tiles_as_vector = Cinder::generate_bioms<Cinder::Biomes>(_seed, width, height, biomes);

    for (size_t i = 0; i < tiles_as_vector.size(); ++i) {
        for (size_t j = 0; j < tiles_as_vector[0].size(); ++j) {
            map[i * height + j] = static_cast<uint8_t>(tiles_as_vector[i][j]);
        }
    }
}

Map::~Map() {
    delete map;
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
    delete map;

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
