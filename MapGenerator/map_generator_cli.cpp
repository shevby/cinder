#include <cstring>
#include <iostream>

#include "arg_parser.h"
#include "MapGenerator.h"

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
              << "    seed=<seed> (seed is a 64-bit number)\n"
              << "    width=<width>\n"
              << "    height=<height>\n"
              << "    output=<output file>\n"
              << "    sea-level=<level> a number between -0.5 and 0.5\n"
              << "    high-rock-level=<level>\n"
              << "    rock-level=<level>\n"
              << "    river-density=<density> number between 0 and 1. Percentage of shores that have river mouth\n"
              << "    wet-equator=<number> number between 0 and 1. 0 - ignore latitude; 1 - equators are wet, poles are dry\n";
}

int main(int argc, char **argv)
{
    if (argc > 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
        print_help();
        return 0;
    }

    arg_parser args(argc, argv);

    Cinder::MapGenerator mapgen;
    std::string output_file = "map.bin";

    if (args.params.find("seed") == args.params.end()) {
        srand(time(NULL));
        mapgen.seed = rand();
    }
    else {
        INT_PARAM(mapgen.seed, "seed")
    }

    INT_PARAM(mapgen.width, "width")
    INT_PARAM(mapgen.height, "height")
    INT_PARAM(mapgen.sea_level, "sea-level")

    FLOAT_PARAM(mapgen.high_rock_level, "high-rock-level")
    FLOAT_PARAM(mapgen.rock_level, "rock-level")
    FLOAT_PARAM(mapgen.river_density, "river-density")
    FLOAT_PARAM(mapgen.wet_equator, "wet-equator")

    if (args.params.find("output") != args.params.end()) {
        output_file = args.params["output"];
    }

    std::cout << "Generating map with seed " << mapgen.seed << "\n"
              << "width x height = " << mapgen.width << " x " << mapgen.height << "\n"
              << "sea level = " << mapgen.sea_level << "\n"
              << "output file = " << output_file << "\n";

    auto map = mapgen.generate_map();
    map->saveToFile(output_file);

    return 0;
}
