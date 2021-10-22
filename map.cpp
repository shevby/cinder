#include <cstdio>
#include <math.h>
#include <vector>
#include <iostream>

#include "map.h"
#include "perlin_noise.h"

namespace Cinder {

static float interpolate(float left, float right, float quotient) {
    return (1 - quotient) * left + quotient * right;
}

float Map::get_altitude(uint32_t x, uint32_t y) {
    return 0.25 * (
        perlin(seed + 100000 + 0.1 * x + 0.111, seed + 10000 + 0.1 * y + 0.1111) +
        perlin(seed + 200000 + 0.01 * x + 0.111, seed + 20000 + 0.01 * y + 0.1111) +
        perlin(seed + 300000 + 0.005 * x + 0.111, seed + 30000 + 0.005 * y + 0.1111) +
        perlin(seed + 400000 + 0.001 * x + 0.111, seed + 40000 + 0.001 * y + 0.1111)
    );
}

void Map::generate_river_starting_from(uint32_t x, uint32_t y) {
    uint32_t x_prev = x;
    uint32_t y_prev = y;

    while (true) {
        // choose the next tile
        std::vector<std::pair<uint32_t, uint32_t>> neightbour_candidates = {
            {x_prev - 1, y_prev},
            {x_prev + 1, y_prev},
            {x_prev, y_prev - 1},
            {x_prev, y_prev + 1}
        };

        std::vector<std::pair<uint32_t, uint32_t>> neightbours_to_choose;
        for (const auto &candidate : neightbour_candidates) {
            uint32_t candidate_x = candidate.first;
            uint32_t candidate_y = candidate.second;

            if ((candidate_x < 0) || (candidate_x >= height) || (candidate_y < 0) || (candidate_y >= width)) {
                continue;
            }

            if (get_altitude(candidate_x, candidate_y) <= get_altitude(x_prev, y_prev)) {
                continue;
            }

            neightbours_to_choose.push_back(candidate);
        }

        if (neightbours_to_choose.size() == 0) {
            // Impossible to add yet another tile to the river
            break;
        }

        auto next_tile = neightbours_to_choose[rand.rand() % neightbours_to_choose.size()];
        // TODO fix river direction
        rivers[x_prev * height + y_prev].riverEntry = TileBorder::TOP;
        rivers[next_tile.first * height + next_tile.second].riverExit = TileBorder::BOTTOM;

        x_prev = next_tile.first;
        y_prev = next_tile.second;
    }
}

Map::Map(const MapConfig &cfg) :
    width(cfg.width),
    height(cfg.height),
    map(new uint8_t[width * height]),
    rivers(new River[width * height]),
    mapType(MapTypes::WORLD_MAP),
    seed(cfg.seed),
    rand(cfg.seed)
{
    #pragma omp parallel for
    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            float latitude = 2*std::abs(x - (double)height/2)/height; // 0 = equator, 1 = pole

            float temperature = perlin(seed + 0.03 * x + 0.5, seed + 0.03 * y + 0.5);
            float moisture    = interpolate(
                                    perlin(seed + 5000 + 0.02 * x + 0.111, seed + 5000 + 0.02 * y + 0.1111),
                                    0.5 - latitude,
                                    cfg.wet_equator
                                );
            float altitude    = get_altitude(x, y);

            Biomes biom = altitude < cfg.sea_level ? temperature > -0.3 ? Biomes::WATER : Biomes::GLACIER
                        : altitude > cfg.high_rock_level ? Biomes::HIGH_ROCK
                        : altitude > cfg.rock_level ? Biomes::ROCK
                        : moisture > 0.3 ? Biomes::SWAMP
                        : moisture > 0.1 ? Biomes::FOREST
                        : moisture > -0.1 ? Biomes::FIELD
                        : moisture > -0.2 ? Biomes::SAVANNA
                        : Biomes::DESERT;

            map[x * height + y] = static_cast<uint8_t>(biom);
        }
    }

    std::vector<std::pair<uint32_t, uint32_t>> river_mouths;

    #pragma omp parallel
    for (size_t x = 0; x < width; ++x) {
        std::vector<std::pair<uint32_t, uint32_t>> river_mouths_thread_data;
        for (size_t y = 0; y < height; ++y) {
            // skip tile if there is a river
            if (rivers[x * height + y].riverExit != TileBorder::NONE)
                continue;

            // skip water tile
            if (map[x * height + y] == static_cast<uint8_t>(Biomes::WATER))
                continue;
            if (map[x * height + y] == static_cast<uint8_t>(Biomes::GLACIER))
                continue;

            // find a tile on a shore

            std::vector<std::pair<uint32_t, uint32_t>> water_nearby;
            TileBorder border;
            if (x >= 1 && map[(x-1) * height + y] == static_cast<uint8_t>(Biomes::WATER)) {
                water_nearby.push_back(std::make_pair(x-1, y));
                border = TileBorder::LEFT;
            }
            if (x < height - 1 && map[(x+1) * height + y] == static_cast<uint8_t>(Biomes::WATER)) {
                water_nearby.push_back(std::make_pair(x+1, y));
                border = TileBorder::RIGHT;
            }
            if (y >= 1 && map[x * height + y - 1] == static_cast<uint8_t>(Biomes::WATER)) {
                water_nearby.push_back(std::make_pair(x, y-1));
                border = TileBorder::TOP;
            }
            if (y < width - 1 && map[x * height + y + 1] == static_cast<uint8_t>(Biomes::WATER)) {
                water_nearby.push_back(std::make_pair(x, y+1));
                border = TileBorder::BOTTOM;
            }

            if (water_nearby.size() == 0)
                continue;

            if (rand.rand() < (uint64_t(-1)) * cfg.river_density)
                continue;

            // choose a random water neighbour as river mouth
            size_t idx = rand.rand() % water_nearby.size();
            rivers[x * height + y].riverExit = border;
        }

        #pragma omp critical
        river_mouths.insert(river_mouths_thread_data.end(), river_mouths_thread_data.begin(), river_mouths_thread_data.end());
    }

    for (const auto &river_mouth : river_mouths) {
        generate_river_starting_from(river_mouth.first, river_mouth.second);
    }

    #pragma omp parallel for
    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            auto idx = x * height + y;
            if (rivers[idx].riverExit != TileBorder::NONE) {
                map[idx] = static_cast<uint8_t>(Biomes::WATER);
            }
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
