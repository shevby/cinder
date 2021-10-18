#include "biom_generator.h"
#include "perlin_noise.h"
#include "map.h"

#include <iostream>

namespace Cinder {

std::vector<std::vector<Biomes>> generate_bioms_perlin_noise(size_t width, size_t height)
{
    std::vector<std::vector<Biomes>> map;

    for (size_t x = 0; x < width; ++x) {
        std::vector<Biomes> row;
        for (size_t y = 0; y < height; ++y) {
            auto noise = perlin(x + 0.5, y + 0.5);
            std::cout << noise << "\n";
            row.push_back(noise > 0 ? Biomes::DESERT : Biomes::GLACIER);
        }
        map.push_back(row);
    }
    return map;
}

}; // namespace Cinder
