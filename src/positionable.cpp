#include "positionable.h"

Positionable::Positionable(Position* p) {
    this->position = p;
}

Positionable::~Positionable() {
}

Position* Positionable::get_pos() {
    return position;
}

void Positionable::set_pos(Position* p) {
    this->position = p;
}
