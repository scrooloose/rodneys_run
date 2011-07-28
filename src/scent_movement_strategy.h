#ifndef SCENT_MOVEMENT_STRATEGY_H
#define SCENT_MOVEMENT_STRATEGY_H

#include "movement_strategy.h"
#include "position.h"
#include "a_star_path_finder.h"
#include "positionable.h"
#include "player.h"
#include <vector>
#include "tiles/tile.h"
#include "message_log.h"

class ScentMovementStrategy : public MovementStrategy {
    private:
        void detect_last_known_pos();
        Position last_known_pos;
        Player* get_player();
        bool can_see_player();
        Position adj_pos_with_strongest_scent();
        bool can_follow_scent();

    public:
        ScentMovementStrategy(Map* m, Positionable* mobile);
        void move();
        bool can_move();
};

#endif
