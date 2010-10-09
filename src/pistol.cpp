#include "pistol.h"

Pistol::Pistol(Map* map, Position p) : RangedWeapon( map, "Pistol", "pistol", p) {
}

int Pistol::get_max_range() {
    return 9;
}

int Pistol::get_dmg_dice() {
    return 3;
}

int Pistol::get_dmg_dice_sides() {
    return 4;
}

int Pistol::get_dmg_modifier() {
    return 2;
}

string Pistol::get_name() {
    return "Pistol";
}

string Pistol::get_ammo_type() {
    return "9mm_round";
}
