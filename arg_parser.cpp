#include <iostream>

#include "arg_parser.h"

arg_parser::arg_parser(int argc, char **argv) {
    if (argc <= 1) {
        // There is no command-line argument
        return;
    }

    cmd = argv[1];

    for (size_t i = 2; i < argc; ++i) {
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

void arg_parser::debug_print() {
    std::cout << "Command: " << cmd << "\n"
              << "Number of parameters: " << params.size() << "\n";

    for (const auto &it : params) {
        std::cout << it.first << " ----> " << it.second << "\n";
    }
}
