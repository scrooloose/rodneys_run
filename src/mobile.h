#ifndef MOBILE_H
#define MOBILE_H

#include "renderable.h"
#include "positionable.h"
#include "position.h"
#include "map.h"
#include "turn_timer.h"

class Mobile : public Renderable, public Positionable {
    protected:
        Map* map;
        int health;
        TurnTimer* turn_timer;

        void reset_turn_timer();
        virtual void take_turn() = 0;
        void killed();

    public:
        Mobile(Position p, Map* m, int turn_length);
        ~Mobile();

        void set_pos(const Position& p);
        bool is_visible_from(Position p);

        bool tick();

        void take_damage(int damage);
        virtual int get_attack_damage() = 0;

};


#endif
