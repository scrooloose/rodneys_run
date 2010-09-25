#ifndef RANGED_WEAPON_H
#define RANGED_WEAPON_H

#include "position.h"
#include "weapon.h"
#include "positionable.h"
#include "map.h"
#include "mobile.h"
#include "message_log.h"
#include "inventory.h"
#include <stdio.h>
#include <string>

class RangedWeapon : public Weapon {
    private:
        int min_range;
        int max_range;
        Inventory* player_inv;
        string ammo_type;

    public:
        RangedWeapon(int min_range, int max_range, Positionable* player, Inventory* player_inv, string ammo_type, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier);
        bool in_range(Position p);
        bool has_ammo();
        virtual bool attack(Position pos);
        virtual string get_range_desc();
};

#endif
