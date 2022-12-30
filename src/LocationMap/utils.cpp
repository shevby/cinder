#include <cstdlib>
#include <cstdio>

#include "utils.h"

bool is_valid_json(const std::string &json) {
    static const std::string filename = "/tmp/is_valid_json.tmp";
    save_string_to_file(json, filename);

    return !system(("python3 ../is_valid_json.py " + filename).c_str());
}

void save_string_to_file(const std::string &content, const std::string &filename) {
    FILE *f;

    f = fopen(filename.c_str(), "wb");
    if (!f) {
        return;
    }

    fwrite(&content[0], 1, content.size(), f);
    fclose(f);
}

std::string join(const std::vector<std::string> &strings, const std::string &delimiter) {
    std::string res;
    for (size_t i=0; i<strings.size(); ++i) {
        res += (i == 0 ? "" : delimiter) + strings[i];
    }
    return res;
}
