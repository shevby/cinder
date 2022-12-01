#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <vector>

const std::string TAB = "    "; // 4 spaces

enum class CreatureType {
    Tree,
    Berry,
    Rabbit,
    Wolf,
    Human,
};

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

struct Creature {
    CreatureType type;
    std::string symbol;
    size_t id;
    int hp;
    int max_hp;
    int age;
    int max_age;
    bool is_grass;
    bool is_meat;
    bool can_eat_grass;
    bool can_eat_meat;
    int hunger;
    int max_hunger;
    int hunger_rate;
    int nutrition_value;
    int attack;

    void tick() {
        ++age;
        if (age > max_age) {
            hp -= (age - max_age);
        }

        hunger += hunger_rate;
        if (hunger > max_hunger) {
            hp -= (hunger - max_hunger);
        }
    }

    bool is_dead() {
        return hp < 0;
    }

    std::vector<std::string> to_json_lines() {
#define CREATURE_JSON_ADD_INT(PARAM) \
    res.push_back(TAB + "\"" #PARAM "\": " + std::to_string(PARAM) + ",");
        std::vector<std::string> res;
        res.push_back("{");
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
        res.push_back(TAB + "\"type\": \"" + creatureTypeToString(type) + "\"");
        res.push_back("}");
        return res;
    }
};

struct Tile {
    std::vector<std::shared_ptr<Creature>> creatures;

    void remove_dead() {
        std::vector<std::shared_ptr<Creature>> res;
        for (auto c: creatures) {
            if (!c->is_dead()) {
                res.push_back(c);
            }
        }
        creatures = res;
    }

    void bite_each_other() {
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

    void tick() {
        for (auto creature: creatures) {
            creature->tick();
        }
        bite_each_other();
        remove_dead();
    }

    std::vector<std::string> to_json_lines() {
        std::vector<std::string> res;
        res.push_back("{");
        res.push_back(TAB + "\"creatures\": [");
        for (size_t i=0; i<creatures.size(); ++i) {
            for (auto line: creatures[i]->to_json_lines()) {
                res.push_back(TAB + TAB + line + "");
            }
            if (i != creatures.size() - 1) {
                res[res.size()-1] += ",";
            }
        }
        res.push_back(TAB + "]");
        res.push_back("}");
        return res;
    }
};

constexpr size_t WIDTH = 30;
constexpr size_t HEIGHT = 30;

struct Map {
    std::vector<std::vector<Tile>> tiles;
    Map() {
        for (size_t i=0; i<HEIGHT; ++i) {
            tiles.emplace_back(std::vector<Tile>(WIDTH));
        }
    }
    void tick() {
        for (size_t i=0; i<HEIGHT; ++i) {
            for (size_t j=0; j<WIDTH; ++j) {
                tiles[i][j].tick();
            }
        }
    }

    std::vector<std::string> to_json_lines() {
        std::vector<std::string> res;
        res.push_back("{");
        res.push_back(TAB + "\"tiles\": [");
        for (size_t i=0; i<HEIGHT; ++i) {
            res.push_back(TAB + TAB + "[");
            for (size_t j=0; j<WIDTH; ++j) {
                res.push_back(TAB + TAB + TAB + "[");
                for (auto line: tiles[i][j].to_json_lines()) {
                    res.push_back(TAB + TAB + TAB + TAB + line);
                }
                res.push_back(TAB + TAB + TAB + ((j == WIDTH - 1) ? "]" : "],"));
            }
            res.push_back(TAB + TAB + ((i == HEIGHT - 1) ? "]" : "],"));
        }
        res.push_back(TAB + "]");
        res.push_back("}");
        return res;
    }

    std::string to_json() {
        std::string res;
        for (auto line: to_json_lines()) {
            res += line + "\n";
        }
        return res;
    }
};

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

int main() {
    Map map;
    for (size_t i=0; i<HEIGHT; ++i) {
        for (size_t j=0; j<WIDTH; ++j) {
            int creature_number = rand() % 5;
            for (int k=0; k<creature_number; ++k) {
                map.tiles[i][j].creatures.emplace_back(make_creature(random_creature()));
            }
        }
    }

    while(true) {
        std::cout << "-------------------------------------------------------------------\n\n";
        std::cout << map;
        map.tick();
        sleep(1);
    }
}