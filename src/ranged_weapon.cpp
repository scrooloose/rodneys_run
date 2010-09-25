#include "ranged_weapon.h"

RangedWeapon::RangedWeapon(int min_range, int max_range, Positionable* player, Inventory* player_inv, string ammo_type, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier) :
              Weapon(player, map, name, dmg_dice, dmg_dice_sides, dmg_modifier) {
    this->min_range = min_range;
    this->max_range = max_range;
    this->player_inv = player_inv;
    this->ammo_type = ammo_type;
}

bool RangedWeapon::in_range(Position p) {
    int actual_range = player->get_pos()->positions_between(&p).size() - 1;
    return actual_range <= max_range && actual_range >= min_range;
}

bool RangedWeapon::has_ammo() {
    return this->player_inv->has_item(this->ammo_type);
}

bool RangedWeapon::attack(Position pos) {
    if (!has_ammo()) {
        MessageLog::add_message("CLICK! Out of ammo!");
        return false;
    }

    Mobile* mob = (Mobile*)map->mobile_for(pos);
    if (!mob) {
        MessageLog::add_message("Select a target!");
        return false;
    }

    if (!in_range(pos)) {
        MessageLog::add_message("Out of range!");
        return false;
    }

    player_inv->use_item(ammo_type);


    int dmg = get_dmg();

    char str[100];
    sprintf(str, "BOOM! Your %s does %d damage!", name.c_str(), dmg);
    MessageLog::add_message(str);

    mob->take_damage(dmg);

    return true;
}

string RangedWeapon::get_range_desc() {
    char str[50];
    sprintf(str, "%d-%d", min_range, max_range);
    return str;
}
