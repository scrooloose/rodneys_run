#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "position.h"
#include "positionable.h"
#include "map.h"
#include <cstdlib>

class Weapon {
    protected:
        string name;
        Positionable* player;
        Map* map;

        int dmg_dice;
        int dmg_dice_sides;
        int dmg_modifier;

    public:
        Weapon(Positionable* player, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier);
        string get_name();
        virtual void attack(Position pos) = 0;
        virtual int get_dmg();


};

#endif
