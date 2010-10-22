#include "radial_damage_strategy.h"

RadialDamageStrategy::RadialDamageStrategy(Map* m, int radius) : DamageStrategy(m) {
    this->radius = radius;
}

int RadialDamageStrategy::attack(const Position& pos) {
    Mobile* mob = (Mobile*)map->mobile_for(pos);
    if (!mob) {
        MessageLog::add_message("Select a target!");
        return false;
    }

    int dmg = get_dmg();
    mob->take_damage(dmg);

    int sec_dmg = dmg / 2;
    if (sec_dmg > 0) {
        vector<Mobile*> secondaries = get_secondary_targets(pos);
        for (unsigned i=0; i < secondaries.size(); i++) {
            Mobile* mob = (Mobile*)secondaries.at(i);
            mob->take_damage(sec_dmg);
        }
    }

    return dmg;
}

vector<Mobile*> RadialDamageStrategy::get_secondary_targets(const Position& origin) {
    vector<Mobile*> secondary_targets;


    //for now just assume the dmg radius is 1
    vector<Position> adjacent_positions = origin.adjacent_positions();

    for (unsigned i=0; i < adjacent_positions.size(); i++) {
        Mobile* mob = (Mobile*)map->mobile_for(adjacent_positions.at(i));
        if (mob) {
            secondary_targets.push_back(mob);
        }
    }

    return secondary_targets;
}
