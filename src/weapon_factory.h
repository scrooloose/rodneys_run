#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "weapon.h"
#include "melee_weapon.h"
#include "ranged_weapon.h"
#include "map.h"
#include "position.h"
#include <string>
#include "simple_damage_strategy.h"
#include "radial_damage_strategy.h"

using namespace std;

class WeaponFactory {
    public:
        static MeleeWeapon* build_drawing_pin(Map* m, const Position& p);

        static RangedWeapon* build_pistol(Map* m, const Position& p);
        static RangedWeapon* build_p90(Map* m, const Position& p);
        static RangedWeapon* build_shotgun(Map* m, const Position& p);
};

#endif
