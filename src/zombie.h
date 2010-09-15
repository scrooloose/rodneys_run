#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "mobile.h"
#include "map.h"
#include <string>

class Zombie : public Mobile {
    public:
        Zombie(Position* p, Map* m);
        ~Zombie();

        string to_char();

};

#endif
