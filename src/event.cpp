#include "event.h"

Event::Event(Position target_pos, string msg) : target_pos(target_pos) {
    this->msg = msg;
    this->has_fired = false;
}

void Event::set_player(Positionable* p) {
    this->player = p;
}

bool Event::check() {
    if (has_fired) {
        return false;
    }

    if (player->get_pos().equals(target_pos)) {
        has_fired = true;
        return true;
    }

    return false;
}

string Event::get_msg() {
    return msg;
}
