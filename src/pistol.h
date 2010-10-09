#ifndef PISTOL_H
#define PISTOL_H

#include <string>
#include "positionable.h"
#include "ranged_weapon.h"
using namespace std;

class Pistol : public RangedWeapon {
    public:
        Pistol(Map* map, Position p);

        int get_max_range();
        int get_dmg_dice();
        int get_dmg_dice_sides();
        int get_dmg_modifier();
        string get_ammo_type();
        string get_name();

};

#endif
