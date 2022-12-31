#pragma once

#include <string>
#include <memory>
#include <vector>

#include "LocationMap.h"
#include "JsonConfig.h"

struct CreatureShortState {
    CreatureShortState() = default;
    CreatureShortState(Creature);

    CreatureType type;
    std::vector<std::string> to_json_lines(JsonConfig json_config);
};

struct LocationTileShortState {
    LocationTileShortState() = default;
    LocationTileShortState(Tile);

    std::vector<CreatureShortState> creatures;
    uint32_t row;
    uint32_t column;

    std::vector<std::string> to_json_lines(JsonConfig json_config);
};

struct LocationMapShortState {
    LocationMapShortState() = default;
    LocationMapShortState(const Map &map);

    std::vector<LocationTileShortState> tiles;
    uint64_t tick_id;
    uint32_t width;
    uint32_t height;

    std::vector<std::string> to_json_lines(JsonConfig json_config);

    std::shared_ptr<std::string> to_json(JsonConfig json_config);
    std::shared_ptr<std::string> to_json_human_readable();
    std::shared_ptr<std::string> to_json_short();
};
