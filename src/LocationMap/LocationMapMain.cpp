#include <iostream>
#include <memory>
#include <thread>

#include "LocationMap.h"
#include "LocationMapStateShort.h"
#include "WebServer.h"

constexpr size_t WIDTH = 30;
constexpr size_t HEIGHT = 30;

Map map(WIDTH, HEIGHT);

std::string get_map_content() {
    auto short_map = map.get_short_state();
    auto content = short_map->to_json(JsonConfig());
    return *content;
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
    for (size_t i=0; i<map.get_height(); ++i) {
        for (size_t j=0; j<map.get_width(); ++j) {
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

