#include "zombie.h"

Zombie::Zombie(Position* p, Map* m) : Mobile(p,m,20) {
    this->ai = new MeleeAI(this, m);
}

Zombie::~Zombie() {
}

string Zombie::to_char() {
    return string("z");
}

void Zombie::take_turn() {
    this->ai->do_ai();
}

int Zombie::get_attack_damage() {
    return 10;
}
