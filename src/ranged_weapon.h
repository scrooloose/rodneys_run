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

        int min_range;
        int max_range;
        int ammo_per_turn;
        string ammo_type;

    public:
        RangedWeapon(Map* map, string name, string type, Position p);

        void set_ammo_type(string ammo_type);
        void set_min_range(int min_range);
        void set_max_range(int max_range);
        void set_ammo_per_turn(int ammo_per_turn);

        bool in_range(Position p);
        bool has_ammo();
        virtual bool attack(Position pos);
        virtual string get_range_desc();
        virtual void wielded_by(Positionable* player, Map* m, Inventory* inv);
        bool is_ranged();
};

#endif
