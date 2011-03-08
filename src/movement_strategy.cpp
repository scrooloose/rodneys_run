#include "movement_strategy.h"

MovementStrategy::MovementStrategy(Map* m, Positionable* mob) {
    this->map = m;
    this->mobile = mob;
}
