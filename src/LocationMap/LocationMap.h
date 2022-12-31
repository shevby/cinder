#pragma once

#include <memory>
#include <semaphore>
#include <string>
#include <vector>

enum class CreatureType {
    Tree,
    Berry,
    Rabbit,
    Wolf,
    Human,
};

std::string creatureTypeToString(CreatureType type);

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
    int reproduction_age;

    void tick();
    bool is_dead() const;
    std::vector<std::string> to_json_lines(bool full_map, const std::string &tab) const;
};

std::shared_ptr<Creature> make_creature(CreatureType type);

struct Tile {
    std::vector<std::shared_ptr<Creature>> creatures;

    void remove_dead();
    void bite_each_other();
    void tick();
    std::vector<std::string> to_json_lines(bool full_map, const std::string &tab) const;
};

struct LocationMapShortState;

struct Map {
    std::vector<std::vector<Tile>> tiles;
    Map(uint32_t _width, uint32_t _height);

    void tick();
    std::binary_semaphore semaphore{1};

    std::shared_ptr<std::string> get_content();
    std::shared_ptr<LocationMapShortState> get_short_state();

    uint32_t get_width() const;
    uint32_t get_height() const;
    uint64_t get_tick_id() const;

private:
    std::vector<std::string> to_json_lines(bool full_map, const std::string &tab) const;
    std::string to_json(bool full_map = true, const std::string &tab = "") const;

    std::shared_ptr<std::string> map_cache = std::make_shared<std::string>("");
    std::shared_ptr<LocationMapShortState> short_state_cache = std::make_shared<LocationMapShortState>();

    uint32_t width;
    uint32_t height;
    uint64_t tick_id;
};

std::ostream& operator<< (std::ostream& stream, const Map& map);
