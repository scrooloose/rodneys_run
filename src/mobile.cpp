#include "mobile.h"

Mobile::Mobile(Position p, Map* m, int turn_delay) : Positionable(p) {
    this->map = m;
    this->health = 20;
    this->turn_timer = new TurnTimer(turn_delay);
}

Mobile::~Mobile() {
}

bool Mobile::is_visible_from(Position p) {
    return map->positions_have_los(get_pos(), p);
}

void Mobile::set_pos(const Position& p) {
    map->update_mobile_position(this, get_pos(), p);
    Positionable::set_pos(p);
}

void Mobile::take_damage(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        killed();
    }
}

void Mobile::killed() {
    map->mobile_killed(this);
    delete this;
}

bool Mobile::tick() {
    if (turn_timer->tick()) {
        take_turn();
        return true;
    }
    return false;
}
