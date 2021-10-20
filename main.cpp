#include <cstring>
#include <iostream>

#include "arg_parser.h"
#include "map.h"
#include "sin_parser.h"

using namespace std;

void print_help() {
    std::cout << "Options: \n"
              << "    --run-sin-parser-tests\n"
              << "    --debug-print-arguments (to test arg_parser class)\n"
              << "    --generate-map\n"
              << "        seed=<seed> (seed is a 64-bit number)\n"
              << "        width=<width>\n"
              << "        height=<height>\n"
              << "        output=<output file>\n"
              << "        sea-level=<level> a number between -0.5 and 0.5\n";
}

int main(int argc, char **argv)
{
    arg_parser args(argc, argv);

    if (args.cmd == "") {
        print_help();
        return 1;
    }

    if (args.cmd == "--debug-print-arguments") {
        args.debug_print();
        return 0;
    }

    if (args.cmd == "--run-sin-parser-tests") {
        Cinder::run_sin_parser_tests();
        return 0;
    }

    if (args.cmd == "--generate-map") {
        Cinder::MapConfig cfg;
        std::string output_file = "map.bin";

        if (args.params.find("seed") == args.params.end()) {
            srand(time(NULL));
            cfg.seed = rand();
        }
        else {
            cfg.seed = std::strtoul(args.params["seed"].c_str(), NULL, 10);
        }

        if (args.params.find("width") != args.params.end()) {
            cfg.width = std::strtoul(args.params["width"].c_str(), NULL, 10);
        }

        if (args.params.find("height") != args.params.end()) {
            cfg.height = std::strtoul(args.params["height"].c_str(), NULL, 10);
        }

        if (args.params.find("sea-level") != args.params.end()) {
            cfg.sea_level = std::stof(args.params["sea-level"].c_str(), NULL);
        }

        if (args.params.find("output") != args.params.end()) {
            output_file = args.params["output"];
        }

        std::cout << "Generating map with seed " << cfg.seed << "\n"
                  << "width x height = " << cfg.width << " x " << cfg.height << "\n"
                  << "sea level = " << cfg.sea_level << "\n"
                  << "output file = " << output_file << "\n";

        Cinder::Map map(cfg);

        map.save_to_file(output_file.c_str());
        return 0;
    }

    print_help();
    return 1;
}
