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
        Inventory* player_inv;

        virtual int get_min_range();
        virtual int get_max_range() = 0;

    public:
        RangedWeapon(Positionable* player, Inventory* player_inv, Map* map);
        bool in_range(Position p);
        bool has_ammo();
        virtual bool attack(Position pos);
        virtual string get_range_desc();
};

#endif
