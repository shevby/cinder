enum class opCode {
    nop,
    move_left,
    move_right,
    move_up,
    move_down,
    move_relative_left,
    move_relative_right,
    move_relative_up,
    move_relative_down,
    reproduce,
    eat,
    go_to_nearest_food,
};

enum class condition {
    if_hunger_less,
    if_hunger_more,
    if_health_less,
    if_health_more,
    if_age_less,
    if_age_more,
};
