#include <memory>
#include <string>
#include <vector>

enum class CreatureType {
    Tree,
    Berry,
    Rabbit,
    Wolf,
    Human,
};

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
    std::vector<std::string> to_json_lines() const;
};

struct Tile {
    std::vector<std::shared_ptr<Creature>> creatures;

    void remove_dead();
    void bite_each_other();
    void tick();
    std::vector<std::string> to_json_lines();
};

struct Map {
    std::vector<std::vector<Tile>> tiles;
    Map();

    void tick();
    std::vector<std::string> to_json_lines();
    std::string to_json();
};
