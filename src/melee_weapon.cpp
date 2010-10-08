#include "melee_weapon.h"

MeleeWeapon::MeleeWeapon(Positionable* player, Map* map) :
             Weapon(player, map) {
 }

bool MeleeWeapon::attack(Position pos) {
    if (!pos.is_adjacent(player->get_pos())) {
        MessageLog::add_message("Can only melee with adjacent targets!");
        return false;
    }

    Mobile* target = (Mobile*)map->mobile_for(pos);

    if (!target) {
        return false;
    }

    int dmg = get_dmg();
    target->take_damage(dmg);

    MessageLog::add_message(get_dmg_desc(dmg));


    return true;
}
