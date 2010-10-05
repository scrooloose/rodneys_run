#include "positionable.h"

Positionable::Positionable(Position p) : position(p) {
}

Positionable::~Positionable() {
}

const Position& Positionable::get_pos() {
    return position;
}

void Positionable::set_pos(const Position& p) {
    this->position = p;
}
