#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "mobile.h"
#include "map.h"
#include "positionable.h"
#include "message_log.h"
#include <string>
#include "ai.h"
#include "melee_ai.h"

class Zombie : public Mobile {
    private:
        AI* ai;

    public:
        Zombie(Position* p, Map* m);
        ~Zombie();

        string to_char();
        int get_attack_damage();
        void do_ai();
};

#endif
