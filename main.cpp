#include <cstring>
#include <iostream>

#include "map.h"
#include "sin_parser.h"

using namespace std;

constexpr uint32_t MAP_WIDTH = 512;
constexpr uint32_t MAP_HEIGHT = MAP_WIDTH;

void print_help() {
    std::cout << "Options: \n"
              << "    --run-sin-parser-tests\n"
              << "    --generate-map <seed> (seed is a 64-bit number)\n";
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "--run-sin-parser-tests") == 0) {
        Cinder::run_sin_parser_tests();
        return 0;
    }

    if (strcmp(argv[1], "--generate-map") == 0) {
        if (argc != 3) {
            print_help();
            return 1;
        }
        uint64_t seed = std::strtoul(argv[2], NULL, 10);
        Cinder::Map map(MAP_WIDTH, MAP_HEIGHT, seed);
        map.save_to_file("map.bin");
        return 0;
    }

    print_help();
    return 1;
}
