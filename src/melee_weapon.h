#ifndef MELEE_WEAPON_H
#define MELEE_WEAPON_H

#include "weapon.h"
#include "position.h"
#include "message_log.h"
#include "mobile.h"

class MeleeWeapon : public Weapon {
    public:
        MeleeWeapon(Positionable* player, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier);
        virtual void attack(Position pos);

};

#endif
