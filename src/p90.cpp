#include "p90.h"

P90::P90(Map* map, Position p) : RangedWeapon(map, "P90", "p90", p) {
}

int P90::get_max_range() {
    return 8;
}

int P90::get_dmg_dice() {
    return 6;
}

int P90::get_dmg_dice_sides() {
    return 3;
}

int P90::get_dmg_modifier() {
    return 1;
}

string P90::get_name() {
    return "P90";
}

string P90::get_ammo_type() {
    return "9mm_round";
}
