#ifndef RADIAL_DAMAGE_STRATEGY_H
#define RADIAL_DAMAGE_STRATEGY_H

#include "damage_strategy.h"
#include "position.h"
#include "map.h"
#include "mobile.h"

class RadialDamageStrategy : public DamageStrategy {
    private:
        int radius;

        vector<Mobile*> get_secondary_targets(const Position& origin);
        void attack_secondary_targets(int dmg);

    public:
        RadialDamageStrategy(Map* m, int radius);
        int attack(const Position& pos);
};

#endif
