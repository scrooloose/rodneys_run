#include "melee_weapon.h"

MeleeWeapon::MeleeWeapon(Map* map, string name, string type, Position p) : Weapon(map, name, type, p) {
}

bool MeleeWeapon::attack(Position pos) {
    if (!pos.is_adjacent(get_player()->get_pos())) {
        MessageLog::add_message("Can only melee with adjacent targets!");
        return false;
    }

    Mobile* target = (Mobile*)map->mobile_for(pos);

    if (!target) {
        return false;
    }

    int dmg = dmg_strategy->attack(pos);
    MessageLog::add_message(get_dmg_desc(dmg));


    return true;
}

bool MeleeWeapon::is_ranged() {
    return false;
}
