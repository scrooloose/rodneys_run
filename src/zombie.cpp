#include "zombie.h"

Zombie::Zombie(Position* p, Map* m) : Mobile(p,m) {
}

Zombie::~Zombie() {
}

string Zombie::to_char() {
    return string("z");
}
