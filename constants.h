#pragma once

#include <vector>
#include <iostream>
#include <fstream>



namespace Cinder {
    enum class MapTypes {
        WORLD_MAP,
        LOCATION_MAP
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
        NO_RIVER
    };

#pragma pack(push, 1)
    struct BiomeCell {
        Biomes tile: 5;
        RiverDirection river: 3; //RiverDirection
        
        friend std::ostream& operator<<(std::ostream& os, const BiomeCell& bc) {
            os << "<BiomCell" << std::endl;
            os << "tile: " << static_cast<uint32_t>(bc.tile) << std::endl;
            os << "river: " << static_cast<uint32_t>(bc.river) << std::endl;
            os << ">" << std::endl;

            return os;
        }
    };
#pragma pack(pop)

    static_assert(sizeof(BiomeCell) == sizeof(uint8_t), "BiomCell and uint8_t sizes mismatch");

    struct Map {
        MapTypes mapType;
        uint32_t width;
        uint32_t height;

        std::vector<std::vector<BiomeCell>> map;

        void save(std::string filePath) {
            using namespace std;
            ofstream outFile(filePath, ios::out|ios::binary);
            outFile.write((char*)&mapType, sizeof(MapTypes));
            outFile.write((char*)&width, sizeof(width));
            outFile.write((char*)&height, sizeof(height));

            for(auto & row : map) {
                outFile.write((char*)row.data(), width);
            }

            outFile.flush();
            outFile.close();

        }
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

    struct Biome {
        Biomes biomType;
        bool hasSnow;
        //uint8 hasRiver;
        TileBorder riverEntry;
        TileBorder riverExit;

        Biome(Biomes biomType){
            this->biomType = biomType;
        }
    };

    struct Village {
        float x;
        float y;
        uint8_t population;
    };
} // namespace Cinder

