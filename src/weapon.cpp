#include "weapon.h"

Weapon::Weapon(Map* map, string name, string type, Position p) : Item(name, type, 1, string("}"), p) {
    this->map = map;
    this->player = NULL;
}

string Weapon::get_dmg_desc(int dmg) {
    char str[100];
    sprintf(str, "Your %s inflicts %d damage!", get_name().c_str(), dmg);
    return string(str);
}

void Weapon::wielded_by(Positionable* player) {
    this->player = player;
}

bool Weapon::is_wieldable() {
    return true;
}

Positionable* Weapon::get_player() {
    if (player == NULL) {
        throw new runtime_error("Weapon::get_player() - weapon hasn't been wielded.");
    }
    return player;
}

void Weapon::set_dmg_strategy(DamageStrategy* dmg_strategy) {
    this->dmg_strategy = dmg_strategy;
}

string Weapon::get_dmg_dice_desc() {
    return this->dmg_strategy->get_dmg_dice_desc();
}
