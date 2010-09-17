#include "zombie.h"

Zombie::Zombie(Position* p, Map* m) : Mobile(p,m) {
    state = s_waiting;
}

Zombie::~Zombie() {
}

string Zombie::to_char() {
    return string("z");
}

void Zombie::do_ai() {
    detect_state();
    switch (state) {
        case s_waiting:
            break;
        case s_attacking:
            attack();
            break;
        case s_approaching:
            approach();
            break;

    }
}

void Zombie::detect_state() {
    switch (state) {
        case s_waiting:
            if (in_attack_range()) {
                state = s_attacking;
            } else {
                state = s_approaching;
            }
            break;
        case s_approaching:
            if (in_attack_range()) {
                state = s_attacking;
            }

        case s_attacking:
            if (!in_attack_range()) {
                state = s_approaching;
            }
            break;
    }
}

bool Zombie::in_attack_range() {
    return position->distance_to(map->get_player()->get_pos()) == 1;
}

void Zombie::attack() {
    MessageLog::add_message("Zombie: attacking");
}

void Zombie::approach() {
    MessageLog::add_message("Zombie: approaching");

    vector<Position> path_to_player = position->positions_between(map->get_player()->get_pos());

    if (path_to_player.size() < 2) {
        return;
    }

    Tile* tile = map->tile_for(path_to_player[1]);
    if (tile->is_walkable()) {
        set_pos(new Position(path_to_player[1]));
    }
}
