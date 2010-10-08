#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "position.h"
#include "positionable.h"
#include "map.h"
#include <cstdlib>
#include <cstdio>

class Weapon {
    protected:
        string name;
        Positionable* player;
        Map* map;

        virtual int get_dmg_dice() = 0;
        virtual int get_dmg_dice_sides() = 0;
        virtual int get_dmg_modifier() = 0;

        virtual string get_dmg_desc(int dmg);

    public:
        Weapon(Positionable* player, Map* map);

        virtual string get_ammo_type() = 0;
        virtual string get_name() = 0;

        virtual bool attack(Position pos) = 0;
        virtual int get_dmg();
        virtual string get_dmg_dice_desc();



};

#endif
