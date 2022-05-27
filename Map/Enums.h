namespace Cinder {

enum class MapTypes {
    WORLD_MAP,
    LOCATION_MAP,
};

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

enum class RiverDirection {
    TOP_DOWN = 0,
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
    DOWN_LEFT = LEFT_DOWN,
    NO_RIVER,
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

    MUSHROOMS_BEGIN,
    BOLETUS = MUSHROOMS_BEGIN,
    FLY_AGARIC,
    SHROOMS,
    MUSHROOMS_END,

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

enum class TileBorder {
    NONE = 0,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

} // namespace Cinder
