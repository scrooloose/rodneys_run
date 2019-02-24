#include "cutscene.h"

Cutscene::Cutscene(Position target_pos, string msg) : Positionable(target_pos), target_pos(target_pos) {
    this->msg = msg;
    this->has_fired = false;
}

void Cutscene::set_player(Positionable* p) {
    this->player = p;
}

void Cutscene::fired() {
    has_fired = true;
}

bool Cutscene::get_fired() {
    return has_fired;
}

bool Cutscene::check() {
    if (has_fired) {
        return false;
    }

    if (player->get_pos().equals(target_pos)) {
        has_fired = true;
        return true;
    }

    return false;
}

string Cutscene::get_msg() {
    return msg;
}

string Cutscene::to_char() {
    return "i";
}
int Cutscene::color_pair() {
    return 1;
}
