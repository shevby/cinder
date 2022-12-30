#include <iostream>
#include <memory>
#include <thread>

#include "LocationMap.h"
#include "WebServer.h"

constexpr size_t WIDTH = 30;
constexpr size_t HEIGHT = 30;

Map map;

std::string get_map_content() {
    std::shared_ptr<std::string> ptr = map.get_content();
    std::string content = *ptr;
    return content;
}

CreatureType random_creature() {
    switch (rand() % 5) {
    case 0: return CreatureType::Tree;
    case 1: return CreatureType::Berry;
    case 2: return CreatureType::Rabbit;
    case 3: return CreatureType::Wolf;
    case 4: return CreatureType::Human;
    }
    return CreatureType::Tree;
}

int main() {
    for (size_t i=0; i<HEIGHT; ++i) {
        for (size_t j=0; j<WIDTH; ++j) {
            int creature_number = rand() % 5;
            for (int k=0; k<creature_number; ++k) {
                map.tiles[i][j].creatures.emplace_back(make_creature(random_creature()));
            }
        }
    }

    std::thread web_thread(server_thread, get_map_content, CompressionMethod::NO_COMPRESSION);

    while(true) {
        std::cout << "-------------------------------------------------------------------\n\n";
        std::cout << map;
        map.tick();
        sleep(1);
    }
}

