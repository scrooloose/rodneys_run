#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include "positionable.h"
#include "position.h"
#include "map.h"

class MovementStrategy {
    protected:
        Map* map;
        Positionable* mobile;

    public:
        MovementStrategy(Map* m, Positionable* mobile);
        virtual void move() = 0;

};

#endif
