#include "weapon.h"

Weapon::Weapon(Positionable* player, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier) {
    this->player = player;
    this->map = map;
    this->name = name;
    this->dmg_dice = dmg_dice;
    this->dmg_dice_sides = dmg_dice_sides;
    this->dmg_modifier = dmg_modifier;
}

string Weapon::get_name() {
    return this->name;
}

int Weapon::get_dmg() {
    int dmg = dmg_modifier;
    for (int i = 0; i < dmg_dice; i++) {
        dmg += (rand() % dmg_dice_sides) + 1;
    }

    return dmg;
}
