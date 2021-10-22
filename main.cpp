#include <cstring>
#include <iostream>

#include "arg_parser.h"
#include "map.h"
#include "sin_parser.h"

#define INT_PARAM(DEST, NAME) \
    if (args.params.find(NAME) != args.params.end()) { \
        DEST = std::strtoul(args.params[NAME].c_str(), NULL, 10); \
    }

#define FLOAT_PARAM(DEST, NAME) \
        if (args.params.find(NAME) != args.params.end()) { \
            DEST = std::stof(args.params[NAME].c_str(), NULL); \
        }

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
              << "        sea-level=<level> a number between -0.5 and 0.5\n"
              << "        high-rock-level=<level>\n"
              << "        rock-level=<level>\n"
              << "        river-density=<density> number between 0 and 1. Percentage of shores that have river mouth\n"
              << "        wet-equator=<number> number between 0 and 1. 0 - ignore latitude; 1 - equators are wet, poles are dry\n";
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
            INT_PARAM(cfg.seed, "seed")
        }

        INT_PARAM(cfg.width, "width")
        INT_PARAM(cfg.height, "height")
        INT_PARAM(cfg.sea_level, "sea-level")

        FLOAT_PARAM(cfg.high_rock_level, "high-rock-level")
        FLOAT_PARAM(cfg.rock_level, "rock-level")
        FLOAT_PARAM(cfg.river_density, "river-density")
        FLOAT_PARAM(cfg.wet_equator, "wet-equator")

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
