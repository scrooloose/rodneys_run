#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "position.h"
#include "positionable.h"
#include "map.h"
#include "item.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

class Weapon : public Item {
    private:
        Positionable* player;

    protected:
        Map* map;

        virtual int get_dmg_dice() = 0;
        virtual int get_dmg_dice_sides() = 0;
        virtual int get_dmg_modifier() = 0;

        virtual string get_dmg_desc(int dmg);

        Positionable* get_player();

    public:
        Weapon(Map* map, string name, string type, Position p);

        virtual string get_ammo_type() = 0;

        virtual bool attack(Position pos) = 0;
        virtual int get_dmg();
        virtual string get_dmg_dice_desc();

        virtual void wielded_by(Positionable* player);

        virtual bool is_wieldable();
        virtual bool is_ranged() = 0;


};

#endif
