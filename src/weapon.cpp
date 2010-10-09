#include "weapon.h"

Weapon::Weapon(Map* map, string name, string type, Position p) : Item(name, type, 1, string("}"), p) {
    this->map = map;
    this->player = NULL;
}

int Weapon::get_dmg() {
    int dmg = get_dmg_modifier();
    for (int i = 0; i < get_dmg_dice(); i++) {
        dmg += (rand() % get_dmg_dice_sides()) + 1;
    }

    return dmg;
}

string Weapon::get_dmg_dice_desc() {
    char str[50];
    if (get_dmg_modifier() != 0) {
        sprintf(str, "%dd%d + %d", get_dmg_dice(), get_dmg_dice_sides(), get_dmg_modifier());
    } else {
        sprintf(str, "%dd%d", get_dmg_dice(), get_dmg_dice_sides());
    }

    return string(str);
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
