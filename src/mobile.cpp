#include "mobile.h"

Mobile::Mobile(Position* p, Map* m) : Positionable(p) {
    this->map = m;
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
