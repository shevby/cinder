#include "LocationMapStateShort.h"
#include "LocationMap.h"
#include "utils.h"

std::vector<std::string> CreatureShortState::to_json_lines(JsonConfig json_config) {
    return {
        "{",
        json_config.tab + "\"type\": \"" + creatureTypeToString(type) + "\"",
        "}",
    };
}

std::vector<std::string> LocationTileShortState::to_json_lines(JsonConfig json_config) {
    std::vector<std::string> res = {
        "{",
        json_config.tab + "\"row\": " + std::to_string(row),
        json_config.tab + "\"column\": " + std::to_string(column),
        json_config.tab + "\"creatures\": ["
    };

    for (size_t i=0; i<creatures.size(); ++i) {
        for (auto line: creatures[i].to_json_lines(json_config)) {
            res.push_back(json_config.tab + json_config.tab + line);
        }
        if (i != creatures.size() - 1) {
            res[res.size()-1] += ",";
        }
    }
    res.push_back(json_config.tab + "]");
    res.push_back("}");
    return res;
}

std::vector<std::string> LocationMapShortState::to_json_lines(JsonConfig json_config) {
    std::vector<std::string> res = {
        "{",
        json_config.tab + "\"tick_id\": " + std::to_string(tick_id),
        json_config.tab + "\"width\": "   + std::to_string(width),
        json_config.tab + "\"height\": "  + std::to_string(height),
        json_config.tab + "\"tiles: [",
    };

    for (size_t i=0; i<tiles.size(); ++i) {
        for (auto line: tiles[i].to_json_lines(json_config)) {
            res.push_back(json_config.tab + json_config.tab + line);
        }
        if (i != tiles.size() - 1) {
            res[res.size()-1] += ",";
        }
    }

    res.push_back(json_config.tab + "]");
    res.push_back("}");

    return res;
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
