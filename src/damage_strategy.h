#ifndef DAMAGE_STRATEGY_H
#define DAMAGE_STRATEGY_H

#include "position.h"
#include "map.h"

class DamageStrategy {
    protected:
        Map* map;
        int dmg_dice;
        int dmg_dice_sides;
        int dmg_modifier;
        virtual int get_dmg();

    public:
        DamageStrategy(Map* m);
        virtual int attack(const Position& p) = 0;
        void set_dmg_dice(int dice, int sides, int modifier);
        virtual string get_dmg_dice_desc();
        void set_map(Map* m);
};

#endif
