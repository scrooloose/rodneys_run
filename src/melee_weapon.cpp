#include "melee_weapon.h"

MeleeWeapon::MeleeWeapon(Positionable* player, Map* map, string name, int dmg_dice, int dmg_dice_sides, int dmg_modifier) :
             Weapon(player, map, name, dmg_dice, dmg_dice_sides, dmg_modifier) {
 }

bool MeleeWeapon::attack(Position pos) {
    if (!pos.is_adjacent(&player->get_pos())) {
        MessageLog::add_message("Can only melee with adjacent targets!");
        return false;
    }

    Mobile* target = (Mobile*)map->mobile_for(pos);

    if (!target) {
        MessageLog::add_message("You swing wildy at the air!");
        return false;
    }

    int dmg = get_dmg();

    char str[100];
    sprintf(str, "Smack! Your %s inflict %d damage!", name.c_str(), dmg);
    MessageLog::add_message(str);

    target->take_damage(dmg);

    return true;
}
