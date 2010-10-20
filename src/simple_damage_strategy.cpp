#include "simple_damage_strategy.h"

SimpleDamageStrategy::SimpleDamageStrategy(Map* m) : DamageStrategy(m) {
}

int SimpleDamageStrategy::attack(const Position& pos) {
    Mobile* mob = (Mobile*)map->mobile_for(pos);
    if (!mob) {
        MessageLog::add_message("Select a target!");
        return false;
    }

    int dmg = get_dmg();
    mob->take_damage(dmg);

    return dmg;
}
