#include "ranged_weapon.h"

RangedWeapon::RangedWeapon(Map* map, string name, string type, Position p) :
              Weapon(map, name, type, p)
{
    this->player_inv = player_inv;
}

bool RangedWeapon::in_range(Position p) {
    int actual_range = get_player()->get_pos().positions_between(p).size() - 1;
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
    mob->take_damage(dmg);

    MessageLog::add_message(get_dmg_desc(dmg));

    return true;
}

string RangedWeapon::get_range_desc() {
    char str[50];
    sprintf(str, "%d-%d", min_range, max_range);
    return str;
}

void RangedWeapon::wielded_by(Positionable* player, Inventory* inv) {
    this->player_inv = inv;
    Weapon::wielded_by(player);
}

bool RangedWeapon::is_ranged() {
    return true;
}

void RangedWeapon::set_min_range(int min_range) {
    this->min_range = min_range;
}

void RangedWeapon::set_max_range(int max_range) {
    this->max_range = max_range;
}

void RangedWeapon::set_ammo_type(string ammo_type) {
    this->ammo_type = ammo_type;
}
