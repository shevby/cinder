#include <iostream>

#include "map.h"
#include "biom_generator.h"

using namespace std;

constexpr uint32_t MAP_WIDTH = 512;
constexpr uint32_t MAP_HEIGHT = MAP_WIDTH;

int main()
{
    Cinder::Map map;
    map.width = MAP_WIDTH;
    map.height = MAP_HEIGHT;
    map.map = new uint8_t[map.width * map.height];

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

    auto tiles_as_vector = Cinder::generate_bioms<Cinder::Biomes>(time(NULL), MAP_WIDTH, MAP_HEIGHT, biomes);

    for (size_t i = 0; i < tiles_as_vector.size(); ++i) {
        for (size_t j = 0; j < tiles_as_vector[0].size(); ++j) {
            map.map[i * map.height + j] = static_cast<uint8_t>(tiles_as_vector[i][j]);
        }
    }

    return 0;
}
