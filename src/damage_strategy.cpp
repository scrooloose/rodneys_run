#include "damage_strategy.h"

DamageStrategy::DamageStrategy(Map* m) {
    this->map = m;
}

void DamageStrategy::set_dmg_dice(int dice, int sides, int modifier) {
    this->dmg_dice = dice;
    this->dmg_dice_sides = sides;
    this->dmg_modifier = modifier;
}

int DamageStrategy::get_dmg() {
    int dmg = dmg_modifier;
    for (int i = 0; i < dmg_dice; i++) {
        dmg += (rand() % dmg_dice_sides) + 1;
    }

    return dmg;
}

string DamageStrategy::get_dmg_dice_desc() {
    char str[50];
    if (dmg_modifier != 0) {
        sprintf(str, "%dd%d + %d", dmg_dice, dmg_dice_sides, dmg_modifier);
    } else {
        sprintf(str, "%dd%d", dmg_dice, dmg_dice_sides);
    }

    return string(str);
}

void DamageStrategy::set_map(Map* m) {
    this->map = m;
}
