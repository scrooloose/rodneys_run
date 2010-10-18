#ifndef P_90_H
#define P_90_H

#include <string>
#include "positionable.h"
#include "ranged_weapon.h"
using namespace std;

class P90 : public RangedWeapon {
    public:
        P90(Map* map, Position p);

        int get_max_range();
        int get_dmg_dice();
        int get_dmg_dice_sides();
        int get_dmg_modifier();
        string get_ammo_type();
        string get_name();

};

#endif
