#include "arg_parser.h"

arg_parser::arg_parser(int argc, char **argv) {
    for (size_t i = 1; i < argc; ++i) {
        std::string tmp = argv[i];
        size_t delim_pos = tmp.find("=");
        if (delim_pos == std::string::npos) {
            params[tmp] = "";
        }
        else {
            params[tmp.substr(0, delim_pos)] = tmp.substr(delim_pos + 1, tmp.size() - delim_pos - 1);
        }
    }
}
