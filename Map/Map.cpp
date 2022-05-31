#include <fstream>
#include <iostream>

#include "Map.h"

namespace Cinder {

MapColumn::MapColumn(BiomeCell *_base) : base(_base) {}

BiomeCell& MapColumn::operator[](const size_t row) {
    return base[row];
}

MapColumn Map::operator[](const size_t column) {
    return {map + column * height};
}

bool Map::loadFromFile(const std::string &filename) {
    FILE *f = fopen(filename.c_str(), "rb");
    if (!f) {
        std::cerr << "Can't open " << filename << std::endl;
        return false;
    }

    uint32_t tmp;
    size_t ret = fread(&tmp, 4, 1, f);
    if (ret != 1) {
        std::cerr << "Can't read map type" << std::endl;
        return false;
    }

    mapType = static_cast<MapTypes>(tmp);

    if (mapType != MapTypes::WORLD_MAP) {
        std::cerr << "Only world map supported" << std::endl;
        return false;
    }

    ret = fread(&tmp, 4, 1, f);
    if (ret != 1) {
        std::cerr << "Can't read width" << std::endl;
        return false;
    }
    width = tmp;

    ret = fread(&tmp, 4, 1, f);
    if (ret != 1) {
        std::cerr << "Can't read height" << std::endl;
        return false;
    }
    height = tmp;

    delete map;
    map = new BiomeCell[width * height];
    if (!map) {
        std::cerr << "Cannot allocate memory for the map" << std::endl;
        return false;
    }

    ret = fread(map, 1, width * height, f);
    if (ret != width * height) {
        std::cerr << "Can't read biomes (" << ret << " tiles read)" << std::endl;
        return false;
    }

    return true;
}

void Map::saveToFile(const std::string &filename) {
    FILE *f;

    f = fopen(filename.c_str(), "wb");
    if (!f) {
        return;
    }

    uint32_t _mapType = (uint32_t)mapType;
    fwrite(&_mapType, sizeof(uint32_t), 1, f);
    fwrite(&height, sizeof(uint32_t), 1, f);
    fwrite(&width, sizeof(uint32_t), 1, f);
    fwrite(map, sizeof(uint8_t), width * height, f);

    fclose(f);

}

}; // namespace Cinder

