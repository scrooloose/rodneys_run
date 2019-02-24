#include "cutscene.h"

Cutscene::Cutscene(Position target_pos, string msg) : Positionable(target_pos), target_pos(target_pos) {
    this->msg = msg;
    this->has_fired = false;
}

void Cutscene::fired() {
    has_fired = true;
}

bool Cutscene::get_fired() {
    return has_fired;
}

string Cutscene::get_msg() {
    return msg;
}

string Cutscene::to_char() {
    return "i";
}

int Cutscene::color_pair() {
    return CYAN_ON_BLACK;
}
