#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "position.h"
#include "positionable.h"
#include "map.h"
#include "item.h"
#include <cstdlib>
#include <cstdio>
#include "damage_strategy.h"

using namespace std;

class Weapon : public Item {
    private:
        Positionable* player;

    protected:
        Map* map;
        DamageStrategy* dmg_strategy;


        Positionable* get_player();
        virtual string get_dmg_desc(int dmg);

    public:
        Weapon(Map* map, string name, string type, Position p);

        virtual bool attack(Position pos) = 0;
        virtual void wielded_by(Positionable* player);
        virtual bool is_wieldable();
        virtual bool is_ranged() = 0;
        void set_dmg_strategy(DamageStrategy* dmg_strategy);
        virtual string get_dmg_dice_desc();
};

#endif
