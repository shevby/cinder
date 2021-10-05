#include <vector>
#include <stdlib.h>

#define BIOM_DEMO // TODO: remove in production

#ifdef BIOM_DEMO
#include <iostream>
#include <cstring>
#endif

/**
 * @brief basic biom generator
 *
 * This method randomly distributes biom centers over the map
 * Each tile obtains the type of the closest biom center
 */
template <typename TILE_TYPE>
std::vector<std::vector<TILE_TYPE>> generate_bioms(unsigned int seed, size_t width, size_t height, std::vector<TILE_TYPE> bioms)
{
    srand(seed);

    struct biom_center_t {
        int x;
        int y;
        TILE_TYPE tile;
        biom_center_t(int _x, int _y, int _tile): x(_x), y(_y), tile(_tile) {};
    };

    std::vector<biom_center_t> biom_centers;
    for (auto biom : bioms) {
        biom_centers.push_back(biom_center_t(rand() % width, rand() % height, biom));
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
                double distance = x_diff * x_diff + y_diff * y_diff;
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

#ifdef BIOM_DEMO
int main() {
    //const char *biom_string = "xxx....------^^^^^^~~~~~~~$$$$$#####UUUUUUU"; // many biom types
    const char *biom_string = "..................................XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"; // two biom types
    std::vector<char> bioms;
    for (size_t i = 0; i < strlen(biom_string); ++i) {
        bioms.push_back(biom_string[i]);
    }

    auto map = generate_bioms<char>(time(NULL), 40, 100, bioms);
    for (const auto &row : map) {
        for (const auto tile : row) {
            std::cout << tile;
        }
        std::cout << "\n";
    }
}
#endif
