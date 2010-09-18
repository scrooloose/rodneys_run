#include "zombie.h"

Zombie::Zombie(Position* p, Map* m) : Mobile(p,m) {
    this->ai = new MeleeAI(this, m);
}

Zombie::~Zombie() {
}

string Zombie::to_char() {
    return string("z");
}

void Zombie::do_ai() {
    this->ai->do_ai();
}
