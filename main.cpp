#include <cstring>
#include <iostream>

#include "arg_parser.h"
#include "map.h"
#include "sin_parser.h"

using namespace std;

constexpr uint32_t MAP_WIDTH = 512;
constexpr uint32_t MAP_HEIGHT = MAP_WIDTH;

void print_help() {
    std::cout << "Options: \n"
              << "    --run-sin-parser-tests\n"
              << "    --debug-print-arguments (to test arg_parser class)\n"
              << "    --generate-map\n"
              << "        seed=<seed> (seed is a 64-bit number)\n";
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
        uint64_t seed;
        if (args.params.find("seed") == args.params.end()) {
            srand(time(NULL));
            seed = rand();
        }
        else {
            seed = std::strtoul(args.params["seed"].c_str(), NULL, 10);
        }
        std::cout << "Generating map with seed " << seed << "\n";
        Cinder::Map map(MAP_WIDTH, MAP_HEIGHT, seed);

        map.save_to_file("map.bin");
        return 0;
    }

    print_help();
    return 1;
}
