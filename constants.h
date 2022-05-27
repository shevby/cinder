#pragma once

#include <vector>
#include <fstream>

namespace Cinder {
    struct CinderCellEditorMap {
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

