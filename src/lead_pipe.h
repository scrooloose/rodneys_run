#ifndef LEAD_PIPE_H
#define LEAD_PIPE_H

#include "melee_weapon.h"
#include "positionable.h"
#include "map.h"

class LeadPipe : public MeleeWeapon {
    protected:
        virtual int get_dmg_dice();
        virtual int get_dmg_dice_sides();
        virtual int get_dmg_modifier();

    public:
        LeadPipe(Map* map, Position p);

        virtual string get_ammo_type();
        virtual string get_name();
};

#endif
