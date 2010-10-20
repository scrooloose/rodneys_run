#ifndef SIMPLE_DAMAGE_STRATEGY_H
#define SIMPLE_DAMAGE_STRATEGY_H

#include "damage_strategy.h"
#include "position.h"
#include "map.h"
#include "mobile.h"

class SimpleDamageStrategy : public DamageStrategy {
    public:
        SimpleDamageStrategy(Map* m);
        int attack(const Position& pos);
};

#endif
