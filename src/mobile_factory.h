#ifndef MOBILE_FACTORY_H
#define MOBILE_FACTORY_H

#include "mobile.h"
#include "map.h"
#include "position.h"
#include "scent_movement_strategy.h"
#include "ai.h"
#include "melee_ai.h"

class MobileFactory {
    public:
        static Mobile* build_zombie(Map* m, const Position& p);
        static Mobile* build_giant_spider(Map* m, const Position& p);
        static Mobile* build_rat(Map* m, const Position& p);

};

#endif
