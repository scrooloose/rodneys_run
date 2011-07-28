#include "melee_ai.h"

MeleeAI::MeleeAI(Mobile* mobile, Map* map, MovementStrategy* ms) {
    this->mobile = mobile;
    this->map = map;
    this->state = s_waiting;
    this->movement_strategy = ms;
}

MeleeAI::~MeleeAI() {
}

void MeleeAI::do_ai() {
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

void MeleeAI::detect_state() {
    if (!movement_strategy->can_move()) {
        MessageLog::add_message("Cant move - waiting");
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
    return mobile->get_pos().is_adjacent(get_player()->get_pos());
}

void MeleeAI::attack() {
    get_player()->attacked_by(mobile);
}

void MeleeAI::approach() {
    this->movement_strategy->move();
}

const Position& MeleeAI::get_pos() {
    return mobile->get_pos();
}

void MeleeAI::set_pos(const Position& p) {
    return mobile->set_pos(p);
}

Player* MeleeAI::get_player() {
    return (Player*)map->get_player();
}
