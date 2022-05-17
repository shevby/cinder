#pragma once

#include <cstdint>

#include "stable_random.h"

namespace Cinder {

enum class Biomes {
    WATER = 0,
    FIELD,
    FOREST,
    ROCK,
    HIGH_ROCK,
    GLACIER,
    SWAMP,
    DESERT,
    SAVANNA,
};

enum class TileBorder {
    NONE = 0,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

enum class LocationTiles {
    WATER = 0,
    GRAVEL,
    GROUND,
    GRASS,
    SAND,
    ROCK,
    LAVA,
    ICE,
    SNOW,
    DIRT
};

enum class NaturalObjects {

    TREE_BEGIN = 0,
    OAK = TREE_BEGIN,
    MAPLE,
    SAKURA,
    PINE,
    MAHOGANY,
    PALM,
    COCOA,
    TREE_END,

    BUSH_BEGIN,
    HOPS = BUSH_BEGIN,
    GRAPE,
    LILAC,
    WEED,
    BUSH_END,

    VEGETABLES_BEGIN,
    POTATO = VEGETABLES_BEGIN,
    CARROT,
    CABBAGE,
    SUNFLOWER,
    VEGETABLES_END,

    MASHROOMS_BEGIN,
    BOLETUS = MASHROOMS_BEGIN,
    FLY_AGARIC,
    SHROOMS,
    MASHROOMS_END,

    ORES_BEGIN,
    STONE=ORES_BEGIN,
    COAL,
    DIAMOND,
    IRON,
    COPPER,
    COFFEE,
    SAND,
    GROUND,
    CINDER, //Something like Spice from Dune
    ORES_END
};

enum class RiverDirection {
    NO_RIVER = 0,
    TOP_DOWN,
    DOWN_TOP = TOP_DOWN,
    TOP_LEFT,
    LEFT_TOP = TOP_LEFT,
    TOP_RIGHT,
    RIGHT_TOP = TOP_RIGHT,
    LEFT_RIGHT,
    RIGHT_LEFT = LEFT_RIGHT,
    RIGHT_DOWN,
    DOWN_RIGHT = RIGHT_DOWN,
    LEFT_DOWN,
    DOWN_LEFT = LEFT_DOWN
};

#pragma pack(push, 1)
struct BiomeCell {
    Biomes tile: 5;
    RiverDirection river: 3;
};
#pragma pack(pop)

static_assert(sizeof(BiomeCell) == 1, "BiomeCell is expected to occupy 1 byte");

struct River {
    TileBorder riverEntry;
    TileBorder riverExit;
};

enum class MapTypes {
    WORLD_MAP,
    CELL_MAP
};

struct MapConfig {
    uint64_t seed;
    uint32_t width  = 512;
    uint32_t height = 512;
    float sea_level = 0;
    float high_rock_level = 0.35;
    float rock_level = 0.25;
    float wet_equator = 0.5;
    float river_density = 0.1;
};

struct Map {
    MapTypes mapType;
    uint32_t width;
    uint32_t height;
    BiomeCell *map;
    River *rivers;
    Random rand;

    uint64_t seed;

    Map(const MapConfig &cfg);
    ~Map();

    float get_altitude(uint32_t x, uint32_t y);
    void generate_river_starting_from(uint32_t x, uint32_t y);

    void save_to_file(const char *filename);
};

}; // namespace Cinder

