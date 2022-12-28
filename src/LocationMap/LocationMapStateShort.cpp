#include "LocationMapStateShort.h"
#include "LocationMap.h"

std::vector<std::string> CreatureShortState::to_json_lines(JsonConfig json_config) {
    return {
        "{",
        json_config.tab + "\"type\": " + creatureTypeToString(type),
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
