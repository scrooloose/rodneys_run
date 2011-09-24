#include "turn_timer.h"

TurnTimer::TurnTimer(int delay) {
    this->delay = delay;
    reset();
}

bool TurnTimer::tick() {
    time_left--;
    return time_left <= 0;
}

void TurnTimer::reset() {
    time_left = delay;
}

void TurnTimer::set_remaining_time(int t) {
    time_left = t;
}

bool TurnTimer::is_turn() {
    return time_left <= 0;
}
