#include <iostream>
#include <thread>
#include <unistd.h>

#include "LocationMap.h"
#include "WebServer.h"

const std::string TAB = "    "; // 4 spaces

std::string creatureTypeToString(CreatureType type) {
    switch (type) {
    case CreatureType::Tree:   return "Tree";
    case CreatureType::Berry:  return "Berry";
    case CreatureType::Rabbit: return "Rabbit";
    case CreatureType::Wolf:   return "Wolf";
    case CreatureType::Human:  return "Human";
    }
    return "???";
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

size_t creature_id() {
    static size_t id = 0;
    return ++id;
}

void Creature::tick() {
    ++age;
    if (age > max_age) {
        hp -= (age - max_age);
    }

    hunger += hunger_rate;
    if (hunger > max_hunger) {
        hp -= (hunger - max_hunger);
    }
}

bool Creature::is_dead() const {
    return hp < 0;
}

std::vector<std::string> Creature::to_json_lines(bool full_map, const std::string &tab) const {
#define CREATURE_JSON_ADD_INT(PARAM) \
    res.push_back(tab + "\"" #PARAM "\": " + std::to_string(PARAM) + ",");
    std::vector<std::string> res;
    res.push_back("{");
    if (!full_map) {
        goto end_of_details;
    }
    CREATURE_JSON_ADD_INT(id)
    CREATURE_JSON_ADD_INT(hp)
    CREATURE_JSON_ADD_INT(max_hp)
    CREATURE_JSON_ADD_INT(age)
    CREATURE_JSON_ADD_INT(max_age)
    CREATURE_JSON_ADD_INT(is_grass)
    CREATURE_JSON_ADD_INT(is_meat)
    CREATURE_JSON_ADD_INT(can_eat_grass)
    CREATURE_JSON_ADD_INT(can_eat_meat)
    CREATURE_JSON_ADD_INT(hunger)
    CREATURE_JSON_ADD_INT(max_hunger)
    CREATURE_JSON_ADD_INT(hunger_rate)
    CREATURE_JSON_ADD_INT(nutrition_value)
    CREATURE_JSON_ADD_INT(attack)
    end_of_details:
    res.push_back(tab + "\"type\": \"" + creatureTypeToString(type) + "\"");
    res.push_back("}");
    return res;
}

void Tile::remove_dead() {
    std::vector<std::shared_ptr<Creature>> res;
    for (auto c: creatures) {
        if (!c->is_dead()) {
            res.push_back(c);
        }
    }
    creatures = res;
}

void Tile::bite_each_other() {
    for (auto offender: creatures) {
        for (auto victim: creatures) {
            if (offender->id == victim->id)
                continue;

            if ((offender->can_eat_grass && victim->is_grass) || (offender->can_eat_meat && victim->is_meat)) {
                victim->hp -= offender->attack;
                if (victim->is_dead()) {
                    offender->hunger -= victim->nutrition_value;
                }
            }
        }
    }
}

void Tile::tick() {
    for (auto creature: creatures) {
        creature->tick();
    }
    bite_each_other();
    remove_dead();
}

std::vector<std::string> Tile::to_json_lines(bool full_map, const std::string &tab) const {
    std::vector<std::string> res;
    res.push_back("{");
    res.push_back(tab + "\"creatures\": [");
    for (size_t i=0; i<creatures.size(); ++i) {
        for (auto line: creatures[i]->to_json_lines(full_map, tab)) {
            res.push_back(tab + tab + line + "");
        }
        if (i != creatures.size() - 1) {
            res[res.size()-1] += ",";
        }
    }
    res.push_back(tab + "]");
    res.push_back("}");
    return res;
}

constexpr size_t WIDTH = 30;
constexpr size_t HEIGHT = 30;

Map::Map() {
    for (size_t i=0; i<HEIGHT; ++i) {
        tiles.emplace_back(std::vector<Tile>(WIDTH));
    }
}

std::shared_ptr<Creature> make_creature(CreatureType type);

void Map::tick() {
    for (size_t i=0; i<HEIGHT; ++i) {
        for (size_t j=0; j<WIDTH; ++j) {
            tiles[i][j].tick();
        }
    }

    // Reproduction
    for (size_t i=0; i<HEIGHT; ++i) {
        for (size_t j=0; j<WIDTH; ++j) {
            for (auto creature: tiles[i][j].creatures) {
                if (creature->age < creature->reproduction_age) {
                    continue;
                }

                // If neighbouring tiles are not overpopulated, make a new creature there
                if (i > 0 && tiles[i-1][j].creatures.size() < 4) {
                    tiles[i-1][j].creatures.push_back(make_creature(creature->type));
                }
                if (i < HEIGHT-1 && tiles[i+1][j].creatures.size() < 4) {
                    tiles[i+1][j].creatures.push_back(make_creature(creature->type));
                }
                if (j > 0 && tiles[i][j-1].creatures.size() < 4) {
                    tiles[i][j-1].creatures.push_back(make_creature(creature->type));
                }
                if (j < WIDTH-1 && tiles[i][j+1].creatures.size() < 4) {
                    tiles[i][j+1].creatures.push_back(make_creature(creature->type));
                }
            }
        }
    }
}

std::vector<std::string> Map::to_json_lines(bool full_map, const std::string &tab) const {
    std::vector<std::string> res;
    res.push_back("{");
    res.push_back(tab + "\"tiles\": [");
    for (size_t i=0; i<HEIGHT; ++i) {
        res.push_back(tab + tab + "[");
        for (size_t j=0; j<WIDTH; ++j) {
            res.push_back(tab + tab + tab + "[");
            for (auto line: tiles[i][j].to_json_lines(full_map, tab)) {
                res.push_back(tab + tab + tab + tab + line);
            }
            res.push_back(tab + tab + tab + ((j == WIDTH - 1) ? "]" : "],"));
        }
        res.push_back(tab + tab + ((i == HEIGHT - 1) ? "]" : "],"));
    }
    res.push_back(tab + "]");
    res.push_back("}");
    return res;
}

std::string Map::to_json(bool full_map, const std::string &tab) const {
    std::string res;
    for (auto line: to_json_lines(full_map, tab)) {
        res += line + "\n";
    }
    return res;
}

std::shared_ptr<Creature> make_creature(CreatureType type) {
    auto res = std::make_shared<Creature>();
    res->id = creature_id();
    res->type = type;
    res->age = 0;
    res->hunger = 0;
    switch (type) {
    case CreatureType::Tree:
        res->symbol = "T";
        res->max_hp = 1000;
        res->max_age = 20;
        res->is_grass = false;
        res->is_meat = false;
        res->can_eat_grass = false;
        res->can_eat_meat = false;
        res->max_hunger = 100;
        res->hunger_rate = 0;
        res->nutrition_value = 0;
        res->attack = 0;
        res->reproduction_age = 10;
        break;
    case CreatureType::Berry:
        res->symbol = "B";
        res->max_hp = 10;
        res->max_age = 3;
        res->is_grass = true;
        res->is_meat = false;
        res->can_eat_grass = false;
        res->can_eat_meat = false;
        res->max_hunger = 100;
        res->hunger_rate = 0;
        res->nutrition_value = 5;
        res->attack = 0;
        res->reproduction_age = 2;
        break;
    case CreatureType::Rabbit:
        res->symbol = "R";
        res->max_hp = 50;
        res->max_age = 7;
        res->is_grass = false;
        res->is_meat = true;
        res->can_eat_grass = true;
        res->can_eat_meat = false;
        res->max_hunger = 30;
        res->hunger_rate = 1;
        res->nutrition_value = 30;
        res->attack = 10;
        res->reproduction_age = 3;
        break;
    case CreatureType::Wolf:
        res->symbol = "W";
        res->max_hp = 150;
        res->max_age = 15;
        res->is_grass = false;
        res->is_meat = true;
        res->can_eat_grass = false;
        res->can_eat_meat = true;
        res->max_hunger = 50;
        res->hunger_rate = 3;
        res->nutrition_value = 50;
        res->attack = 50;
        res->reproduction_age = 4;
        break;
    case CreatureType::Human:
        res->symbol = "H";
        res->max_hp = 70;
        res->max_age = 35;
        res->is_grass = false;
        res->is_meat = true;
        res->can_eat_grass = true;
        res->can_eat_meat = true;
        res->max_hunger = 50;
        res->hunger_rate = 3;
        res->nutrition_value = 80;
        res->attack = 20;
        res->reproduction_age = 7;
        break;
    }
    res->hp = res->max_hp;
    return res;
}

std::ostream& operator<< (std::ostream& stream, const Map& map) {
    for (size_t i=0; i<HEIGHT; ++i) {
        for (size_t j=0; j<WIDTH; ++j) {
            std::string text;
            for (auto creature: map.tiles[i][j].creatures) {
                text += creature->symbol;
            }
            text += ".....";
            std::cout << text.substr(0, 5) << " ";
        }
        std::cout << "\n";
    }
    return stream;
}

Map map;

std::string get_map_content() {
    return map.to_json(false, "");
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

    std::thread web_thread(server_thread, get_map_content);

    while(true) {
        std::cout << "-------------------------------------------------------------------\n\n";
        std::cout << map;
        map.tick();
        sleep(1);
    }
}
