#pragma once

namespace Cinder {
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

