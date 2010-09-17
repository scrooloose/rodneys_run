#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "mobile.h"
#include "map.h"
#include "positionable.h"
#include "message_log.h"
#include <string>

class Zombie : public Mobile {
    const static int s_waiting = 1;
    const static int s_fleeing = 2;
    const static int s_attacking = 3;
    const static int s_approaching = 4;
    const static int s_taking_cover = 5;

    int state;


    public:
        Zombie(Position* p, Map* m);
        ~Zombie();

        string to_char();

        void do_ai();
        void detect_state();
        bool in_attack_range();

        void approach();
        void attack();
};

#endif
