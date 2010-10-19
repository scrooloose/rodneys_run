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

        int dmg_dice;
        int dmg_dice_sides;
        int dmg_modifier;

        virtual string get_dmg_desc(int dmg);

        Positionable* get_player();

    public:
        Weapon(Map* map, string name, string type, Position p);

        void set_dmg_dice(int dice, int sides, int modifier);

        virtual bool attack(Position pos) = 0;
        virtual int get_dmg();
        virtual string get_dmg_dice_desc();

        virtual void wielded_by(Positionable* player);

        virtual bool is_wieldable();
        virtual bool is_ranged() = 0;


};

#endif
