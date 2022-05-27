#include "Map.h"

namespace Cinder {

MapColumn::MapColumn(BiomeCell *_base) : base(_base) {}

BiomeCell& MapColumn::operator[](const size_t row) {
    return base[row];
}

MapColumn Map::operator[](const size_t column) {
    return {map + column * height};
}

void Map::save_to_file(const char *filename) {
}

}; // namespace Cinder

