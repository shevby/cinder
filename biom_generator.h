#pragma once

#include <vector>
#include <stdlib.h>

#include "stable_random.h"

namespace Cinder {

/**
 * @brief basic biom generator
 *
 * This method randomly distributes biom centers over the map
 * Each tile obtains the type of the closest biom center
 */
template <typename TILE_TYPE>
std::vector<std::vector<TILE_TYPE>> generate_bioms(unsigned int seed, size_t width, size_t height, std::vector<TILE_TYPE> bioms)
{
    Random rnd(seed);

    struct biom_center_t {
        int x;
        int y;
        TILE_TYPE tile;
        int distance_multiplier;
        biom_center_t(int _x, int _y, TILE_TYPE _tile, int _distance_multiplier):
            x(_x), y(_y), tile(_tile), distance_multiplier(_distance_multiplier) {};
    };

    std::vector<biom_center_t> biom_centers;
    for (auto biom : bioms) {
        biom_centers.push_back(biom_center_t(rnd.rand() % width, rnd.rand() % height, biom, rnd.rand() % 10 + 2));
    }

    std::vector<std::vector<TILE_TYPE>> map;

    for (size_t x = 0; x < width; ++x) {
        std::vector<TILE_TYPE> row;
        for (size_t y = 0; y < height; ++y) {
            TILE_TYPE closest_biom = bioms[0];
            double min_distance = 90000000000000000000000000.0; // a big number
            for (auto biom_center : biom_centers) {
                auto x_diff = std::abs((double)(x - biom_center.x));
                auto y_diff = std::abs((double)(y - biom_center.y));
                double distance = (x_diff * x_diff + y_diff * y_diff) * biom_center.distance_multiplier;
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_biom = biom_center.tile;
                }
            }
            row.push_back(closest_biom);
        }
        map.push_back(row);
    }
    return map;
}

}; // namespace Cinder
