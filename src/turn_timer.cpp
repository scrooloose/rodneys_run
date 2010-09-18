#include "turn_timer.h"

TurnTimer::TurnTimer(int delay) {
    this->delay = delay;
    reset();
}

bool TurnTimer::tick() {
    timer--;
    if (timer == 0) {
        reset();
        return true;
    }
    return false;
}

void TurnTimer::reset() {
    timer = delay;
}

void TurnTimer::set_remaining_time(int t) {
    timer = t;
}
