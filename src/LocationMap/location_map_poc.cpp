#include <iostream>
#include <unistd.h>

#include "LocationMap.h"
#include "Gzip.h"
#include "WebServer.h"
#include "JsonConfig.h"
#include "LocationMapStateShort.h"

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
            res.push_back(tab + tab + line);
        }
        if (i != creatures.size() - 1) {
            res[res.size()-1] += ",";
        }
    }
    res.push_back(tab + "]");
    res.push_back("}");
    return res;
}

Map::Map(uint32_t _width, uint32_t _height)
    : width(_width)
    , height(_height)
    , tick_id(1)
{
    for (size_t i=0; i<height; ++i) {
        tiles.emplace_back(std::vector<Tile>(width));
    }
}

std::shared_ptr<Creature> make_creature(CreatureType type);

void Map::tick() {
    semaphore.acquire();

    for (size_t i=0; i<height; ++i) {
        for (size_t j=0; j<width; ++j) {
            tiles[i][j].tick();
        }
    }

    // Reproduction
    for (size_t i=0; i<height; ++i) {
        for (size_t j=0; j<width; ++j) {
            for (auto creature: tiles[i][j].creatures) {
                if (creature->age < creature->reproduction_age) {
                    continue;
                }

                // If neighbouring tiles are not overpopulated, make a new creature there
                if (i > 0 && tiles[i-1][j].creatures.size() < 4) {
                    tiles[i-1][j].creatures.push_back(make_creature(creature->type));
                }
                if (i < height-1 && tiles[i+1][j].creatures.size() < 4) {
                    tiles[i+1][j].creatures.push_back(make_creature(creature->type));
                }
                if (j > 0 && tiles[i][j-1].creatures.size() < 4) {
                    tiles[i][j-1].creatures.push_back(make_creature(creature->type));
                }
                if (j < width-1 && tiles[i][j+1].creatures.size() < 4) {
                    tiles[i][j+1].creatures.push_back(make_creature(creature->type));
                }
            }
        }
    }

    *map_cache = to_json(false, "");

    ++tick_id;

    short_state_cache->width = width;
    short_state_cache->height = height;
    short_state_cache->tick_id = tick_id;

    short_state_cache->tiles.clear();

    for (size_t row=0; row<tiles.size(); ++row) {
        for (size_t column=0; column<tiles[row].size(); ++column) {
            LocationTileShortState tile_short(tiles[row][column]);
            tile_short.row = row;
            tile_short.column = column;
            short_state_cache->tiles.push_back(tile_short);
        }
    }

    semaphore.release();
}

std::vector<std::string> Map::to_json_lines(bool full_map, const std::string &tab) const {
    LocationMapShortState map_short(*this);
    return map_short.to_json_lines(JsonConfig());
}

std::string Map::to_json(bool full_map, const std::string &tab) const {
    std::string res;
    for (auto line: to_json_lines(full_map, tab)) {
        res += line + "\n";
    }
    return res;
}

std::shared_ptr<std::string> Map::get_content() {
    semaphore.acquire();
    std::shared_ptr<std::string> res = map_cache;
    semaphore.release();
    return res;
}

std::shared_ptr<LocationMapShortState> Map::get_short_state() {
    semaphore.acquire();
    std::shared_ptr<LocationMapShortState> res = short_state_cache;
    semaphore.release();
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
    for (size_t i=0; i<map.get_height(); ++i) {
        for (size_t j=0; j<map.get_width(); ++j) {
            std::string text;
            for (auto creature: map.tiles[i][j].creatures) {
                text += creature->symbol;
            }
            text += "....";
            std::cout << text.substr(0, 4) << " ";
        }
        std::cout << "\n";
    }
    return stream;
}

uint32_t Map::get_height() const {
    return height;
}

uint32_t Map::get_width() const {
    return width;
}

uint64_t Map::get_tick_id() const {
    return tick_id;
}
