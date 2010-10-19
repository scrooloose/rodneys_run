#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "weapon.h"
#include "melee_weapon.h"
#include "ranged_weapon.h"
#include "map.h"
#include "position.h"
#include <string>

using namespace std;

class WeaponFactory {
    public:
        static MeleeWeapon* build_lead_pipe(Map* m, const Position& p);

        static RangedWeapon* build_pistol(Map* m, const Position& p);
        static RangedWeapon* build_p90(Map* m, const Position& p);
};

#endif
