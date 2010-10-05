#include "zombie.h"

Zombie::Zombie(Position p, Map* m) : Mobile(p,m,15) {
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
    //3d6 damage
    int dmg = 0;
    for (int i=0; i < 3; i++) {
        dmg += (rand() % 6)+1;
    }

    return dmg;
}
