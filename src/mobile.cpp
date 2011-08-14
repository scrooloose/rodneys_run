#include "mobile.h"

Mobile::Mobile(Position p, Map* m, int turn_delay) : Positionable(p) {
    this->map = m;
    this->turn_timer = new TurnTimer(turn_delay);
}

Mobile::~Mobile() {
}

void Mobile::set_ai(AI* ai) {
    this->ai = ai;
}

void Mobile::set_renderable_char(string c) {
    this->renderable_char = c;
}

void Mobile::set_attack_dice(int num_dice, int num_sides, int modifier) {
    this->attack_dice = num_dice;
    this->attack_dice_sides = num_sides;
    this->attack_modifier = modifier;
}

void Mobile::set_health(int h) {
    this->health = h;
}

bool Mobile::is_visible_from(Position p) {
    return map->positions_have_los(get_pos(), p);
}

void Mobile::set_pos(const Position& p) {
    map->update_mobile_position(this, get_pos(), p);
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

bool Mobile::tick() {
    if (turn_timer->tick()) {
        take_turn();
        return true;
    }
    return false;
}


int Mobile::get_attack_damage() {
    int dmg = 0;
    for (int i=0; i < attack_dice; i++) {
        dmg += (rand() % attack_dice_sides)+1;
    }

    dmg += attack_modifier;

    return dmg;
}

void Mobile::take_turn() {
    this->ai->do_ai();
}


string Mobile::to_char() {
    return renderable_char;
}
