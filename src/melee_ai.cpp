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
        last_known_pos = &get_player()->get_pos();
    } else {
        if (last_known_pos && get_pos().equals(*last_known_pos)) {
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
    return mobile->get_pos().is_adjacent(get_player()->get_pos());
}

void MeleeAI::attack() {
    get_player()->attacked_by(mobile);
}

void MeleeAI::approach() {
    PathFinder pf(map, get_pos(), get_player()->get_pos());
    list<Position> path = pf.get_path();
    if (path.size() == 0) {

        //mob cant get to player, so give up
        last_known_pos = NULL;
        return;
    }

    list<Position>::iterator i = path.begin();
    i++;

    Position new_pos(*i);

    //check here since PathFinder doesnt take into account other mobs when
    //calculating the path
    if (map->is_walkable(new_pos)) {
        set_pos(new_pos);
    }
}

Position& MeleeAI::get_pos() {
    return mobile->get_pos();
}

void MeleeAI::set_pos(const Position& p) {
    return mobile->set_pos(p);
}

Player* MeleeAI::get_player() {
    return (Player*)map->get_player();
}

bool MeleeAI::can_see_player() {
    return map->positions_have_los(get_player()->get_pos(), get_pos());
}
