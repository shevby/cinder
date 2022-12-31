#include "LocationMapStateShort.h"
#include "LocationMap.h"
#include "utils.h"

CreatureShortState::CreatureShortState(Creature c)
    : type(c.type)
    {}

LocationTileShortState::LocationTileShortState(Tile t) {
    for (auto c: t.creatures) {
        creatures.push_back(CreatureShortState(*c));
    }
}

LocationMapShortState::LocationMapShortState(Map map)
    : width(map.get_width())
    , height(map.get_height())
    , tick_id(map.get_tick_id())
{
}

std::vector<std::string> CreatureShortState::to_json_lines(JsonConfig json_config) {
    return {
        "{",
        json_config.tab + "\"type\": \"" + creatureTypeToString(type) + "\"",
        "}",
    };
}

std::vector<std::string> LocationTileShortState::to_json_lines(JsonConfig json_config) {
    JsonSerializer creatures_json(json_config);;
    for (auto creature: creatures) {
        creatures_json.add_to_array(creature.to_json_lines(json_config));
    }

    JsonSerializer json(json_config);
    json.add("row", row);
    json.add("column", column);
    json.add("creatures", creatures_json.get_json_lines(true));

    return json.get_json_lines();
}

std::vector<std::string> LocationMapShortState::to_json_lines(JsonConfig json_config) {
    JsonSerializer tiles_json(json_config);
    for (auto tile: tiles) {
        tiles_json.add_to_array(tile.to_json_lines(json_config));
    }

    JsonSerializer json(json_config);
    json.add("tick_id", tick_id);
    json.add("width", width);
    json.add("height", height);
    json.add("tiles", tiles_json.get_json_lines(true));

    return json.get_json_lines();
}

std::shared_ptr<std::string> LocationMapShortState::to_json(JsonConfig json_config) {
    return std::make_shared<std::string>(join(to_json_lines(json_config), json_config.newline));
}

std::shared_ptr<std::string> LocationMapShortState::to_json_human_readable() {
    static const JsonConfig json_config = {
        .tab = "    ", // 4 spaces
        .newline = "\n",
    };
    return to_json(json_config);
}

std::shared_ptr<std::string> LocationMapShortState::to_json_short() {
    static const JsonConfig json_config = {
        .tab = "",
        .newline = "",
    };
    return to_json(json_config);
}
