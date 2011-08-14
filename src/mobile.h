#ifndef MOBILE_H
#define MOBILE_H

#include "renderable.h"
#include "positionable.h"
#include "position.h"
#include "map.h"
#include "turn_timer.h"
#include "ai.h"


class Mobile : public Renderable, public Positionable {
    protected:
        Map* map;
        int health;
        TurnTimer* turn_timer;

        void reset_turn_timer();
        void take_turn();
        void killed();

        AI* ai;

        int attack_dice;
        int attack_dice_sides;
        int attack_modifier;

        string renderable_char;

    public:
        Mobile(Position p, Map* m, int turn_length);
        ~Mobile();

        void set_ai(AI* ai);
        void set_attack_dice(int num_dice, int num_sides, int modifier);
        void set_renderable_char(string c);

        void set_pos(const Position& p);
        bool is_visible_from(Position p);

        bool tick();

        void take_damage(int damage);

        int get_attack_damage();
        string to_char();

};


#endif
