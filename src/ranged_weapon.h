#ifndef RANGED_WEAPON_H
#define RANGED_WEAPON_H

#include "position.h"
#include "weapon.h"
#include "positionable.h"
#include "map.h"
#include "mobile.h"
#include "message_log.h"
#include <stdio.h>

class RangedWeapon : public Weapon {
    private:
        int min_range;
        int max_range;

    public:
        RangedWeapon(int min_range, int max_range, Positionable* player, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier);
        bool in_range(Position p);
        virtual bool attack(Position pos);
        virtual string get_range_desc();
};

#endif
