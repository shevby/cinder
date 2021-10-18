#include "biom_generator.h"
#include "perlin_noise.h"
#include "map.h"

#include <iostream>

namespace Cinder {

std::vector<std::vector<Biomes>> generate_bioms_perlin_noise(uint64_t seed, size_t width, size_t height)
{
    std::vector<std::vector<Biomes>> map;

    for (size_t x = 0; x < width; ++x) {
        std::vector<Biomes> row;
        for (size_t y = 0; y < height; ++y) {
            auto noise = perlin(0.1 * x + 0.5, 0.1 * y + 0.5);

            float temperature = perlin(seed + 0.03 * x + 0.5, seed + 0.03 * y + 0.5);
            float moisture    = perlin(seed + 5000 + 0.02 * x + 0.111, seed + 5000 + 0.02 * y + 0.1111);
            float height      = perlin(seed + 100000 + 0.1 * x + 0.111, seed + 10000 + 0.1 * y + 0.1111);

            Biomes biom;

            if (height < 0) {
                biom = temperature > 0 ? Biomes::WATER : Biomes::GLACIER;
            }
            else if (height > 0.35) {
                biom = Biomes::HIGH_ROCK;
            }
            else if (height > 0.25) {
                biom = Biomes::ROCK;
            }
            else {
                if (moisture > 0.3) {
                    biom = Biomes::SWAMP;
                }
                else if (moisture > 0.1) {
                    biom = Biomes::FOREST;
                }
                else if (moisture > -0.1) {
                    biom = Biomes::FIELD;
                }
                else if (moisture > -0.2) {
                    biom = Biomes::SAVANNA;
                }
                else {
                    biom = Biomes::DESERT;
                }
            }

            row.push_back(biom);
        }
        map.push_back(row);
    }
    return map;
}

}; // namespace Cinder
