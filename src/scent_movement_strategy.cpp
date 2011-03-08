#include "scent_movement_strategy.h"

ScentMovementStrategy::ScentMovementStrategy(Map* m, Positionable* mob) : MovementStrategy(m, mob), last_known_pos(Position::null_position()) {}

void ScentMovementStrategy::move() {
    AStarPathFinder pf(map, mobile->get_pos(), map->get_player()->get_pos());
    list<Position> path = pf.get_path();
    if (path.size() == 0) {

        //mob cant get to player, so give up
        last_known_pos = Position::null_position();
        return;
    }

    list<Position>::iterator i = path.begin();
    i++;

    Position new_pos(*i);

    //check here since AStarPathFinder doesnt take into account other mobs when
    //calculating the path
    if (map->is_walkable(new_pos)) {
        mobile->set_pos(new_pos);
    }
}

void ScentMovementStrategy::detect_last_known_pos() {
    if (can_see_player()) {
        last_known_pos = get_player()->get_pos();
    } else {
        if (!last_known_pos.is_null() && mobile->get_pos().equals(last_known_pos)) {
            last_known_pos = Position::null_position();
        }
    }
}

Player* ScentMovementStrategy::get_player() {
    return (Player*)map->get_player();
}

bool ScentMovementStrategy::can_see_player() {
    return map->positions_have_los(map->get_player()->get_pos(), mobile->get_pos());
}
