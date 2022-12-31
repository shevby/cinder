#include "JsonConfig.h"
#include "utils.h"

JsonSerializer::JsonSerializer(JsonConfig _config)
    : config(_config)
    {}

void JsonSerializer::add(const std::string &key, const std::string &value) {
    if (lines.size() > 0) {
        lines[lines.size() - 1] += ",";
    }
    lines.push_back(config.tab + "\"" + key + "\": \"" + value + "\"");
}

void JsonSerializer::add(const std::string &key, int64_t value) {
    if (lines.size() > 0) {
        lines[lines.size() - 1] += ",";
    }
    lines.push_back(config.tab + "\"" + key + "\": " + std::to_string(value));
}

void JsonSerializer::add(const std::string &key, std::vector<std::string> lines_to_add) {
    if (lines.size() > 0) {
        lines[lines.size() - 1] += ",";
    }

    for (size_t i=0; i<lines_to_add.size(); ++i) {
        if (i == 0) {
            lines.push_back(config.tab + "\"" + key + "\": " + lines_to_add[0]);
        }
        else {
            lines.push_back(config.tab + lines_to_add[i]);
        }
    }
}

void JsonSerializer::add_to_array(std::vector<std::string> lines_to_add) {
    if (lines.size() > 0) {
        lines[lines.size() - 1] += ",";
    }

    for (size_t i=0; i<lines_to_add.size(); ++i) {
        lines.push_back(config.tab + lines_to_add[i]);
    }
}

std::vector<std::string> JsonSerializer::get_json_lines(bool is_array) {
    std::vector<std::string> tmp = lines;
    tmp.insert(tmp.begin(), is_array ? "[" : "{");
    tmp.push_back(is_array ? "]" : "}");
    return tmp;
}

std::string JsonSerializer::get_json(bool is_array) {
    return join(get_json_lines(), config.newline);
}
