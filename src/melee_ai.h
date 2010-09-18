#ifndef MELEE_AI_H
#define MELEE_AI_H

#include "ai.h"
#include "position.h"
#include "map.h"
#include "mobile.h"
#include "message_log.h"
#include "player.h"

class MeleeAI : public AI {
    private:
        const static int s_waiting = 1;
        const static int s_fleeing = 2;
        const static int s_attacking = 3;
        const static int s_approaching = 4;
        const static int s_taking_cover = 5;
        int state;

        Mobile* mobile;
        Map* map;

        Position* last_known_pos;

        void detect_state();
        bool in_attack_range();
        void approach();
        void attack();

        Position* get_pos();
        void set_pos(Position* p);
        Player* get_player();

        bool can_see_player();
        void detect_last_known_pos();

    public:
        MeleeAI(Mobile* mobile, Map* map);
        ~MeleeAI();


        void do_ai();

};

#endif
