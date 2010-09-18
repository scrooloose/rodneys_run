#include "mobile.h"

Mobile::Mobile(Position* p, Map* m, int turn_delay) : Positionable(p) {
    this->map = m;
    this->health = 20;
    this->turn_delay = turn_delay;
    reset_turn_timer();
}

Mobile::~Mobile() {
}

bool Mobile::is_visible_from(Position* p) {
    return map->positions_have_los(this->position, p);
}

void Mobile::set_pos(Position* p) {
    map->update_mobile_position(this, *get_pos(), *p);
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

void Mobile::tick() {
    turn_timer--;
    if (turn_timer == 0) {
        take_turn();
        reset_turn_timer();
    }
}

void Mobile::reset_turn_timer() {
    MessageLog::add_message("Mobile: reset_turn_timer");
    turn_timer = turn_delay;
}
