#include "melee_ai.h"

MeleeAI::MeleeAI(Mobile* mobile, Map* map) {
    this->mobile = mobile;
    this->map = map;
    this->state = s_waiting;
}

MeleeAI::~MeleeAI() {
}

void MeleeAI::do_ai() {
    detect_last_known_pos();
    detect_state();
    switch (state) {
        case s_waiting:
            MessageLog::add_message("MeleeAI: waiting");
            break;
        case s_attacking:
            attack();
            break;
        case s_approaching:
            approach();
            break;

    }
}

void MeleeAI::detect_last_known_pos() {
    if (can_see_player()) {
        last_known_pos = get_player()->get_pos();
    } else {
        if (last_known_pos && get_pos()->equals(last_known_pos)) {
            last_known_pos = NULL;
        }
    }
}

void MeleeAI::detect_state() {
    if (!can_see_player() && last_known_pos == NULL) {
        state = s_waiting;
        return;
    }

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

bool MeleeAI::in_attack_range() {
    return mobile->get_pos()->distance_to(map->get_player()->get_pos()) == 1;
}

void MeleeAI::attack() {
    MessageLog::add_message("MeleeAI: attacking");
    get_player()->attacked_by(mobile);
}

void MeleeAI::approach() {
    MessageLog::add_message("MeleeAI: approaching");

    Position* pos_to_approach = last_known_pos;
    vector<Position> path_to_player = get_pos()->positions_between(pos_to_approach);

    if (path_to_player.size() < 2) {
        return;
    }

    Tile* tile = map->tile_for(path_to_player[1]);
    if (tile->is_walkable()) {
        set_pos(new Position(path_to_player[1]));
    }

}

Position* MeleeAI::get_pos() {
    return mobile->get_pos();
}

void MeleeAI::set_pos(Position* p) {
    return mobile->set_pos(p);
}

Player* MeleeAI::get_player() {
    return (Player*)map->get_player();
}

bool MeleeAI::can_see_player() {
    return map->positions_have_los(get_player()->get_pos(), get_pos());
}
