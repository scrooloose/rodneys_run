#include "mobile.h"

Mobile::Mobile(Position* p, Map* m) : Positionable(p) {
    this->map = m;
    this->health = 20;
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
