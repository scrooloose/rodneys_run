#include "mobile.h"

Mobile::Mobile(Position* p, Map* m) : Positionable(p) {
    this->map = m;
}

Mobile::~Mobile() {
}

bool Mobile::is_visible_from(Position* p) {
    return map->positions_have_los(this->position, p);
}
