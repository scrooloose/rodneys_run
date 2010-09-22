#include "ranged_weapon.h"

RangedWeapon::RangedWeapon(int range, Positionable* player, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier) :
              Weapon(player, map, name, dmg_dice, dmg_dice_sides, dmg_modifier) {
    this->range = range;
}

bool RangedWeapon::in_range(Position p) {
    int actual_range = player->get_pos()->positions_between(&p).size() - 2;
    return actual_range <= range;
}

void RangedWeapon::attack(Position pos) {
    Mobile* mob = (Mobile*)map->mobile_for(pos);
    if (!mob) {
        return;
    }

    if (!in_range(pos)) {
        MessageLog::add_message("Out of range!");
        return;
    }


    int dmg = get_dmg();

    char str[100];
    sprintf(str, "BOOM! Your %s does %d damage!", name.c_str(), dmg);
    MessageLog::add_message(str);


    mob->take_damage(dmg);
}
