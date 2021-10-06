#include <vector>

#include "biom_generator.h"
#include "map.h"

namespace Cinder {

Map::Map(uint32_t _width, uint32_t _height, uint64_t _seed) :
    width(_width),
    height(_height),
    map(new uint8_t[width * height])
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

}; // namespace Cinder
