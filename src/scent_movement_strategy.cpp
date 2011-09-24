#include "scent_movement_strategy.h"

ScentMovementStrategy::ScentMovementStrategy(Map* m, Positionable* mob) : MovementStrategy(m, mob), last_known_pos(Position::null_position()) {}

void ScentMovementStrategy::move() {
    Position new_pos = Position::null_position();

    if (can_see_player()) {
        AStarPathFinder pf(map, mobile->get_pos(), map->get_player()->get_pos());
        list<Position> path = pf.get_path();
        if (path.size() == 0) {
            return;
        }

        list<Position>::iterator i = path.begin();
        i++;

        new_pos = Position(*i);

    } else if (can_follow_scent()) {
        new_pos = adj_pos_with_strongest_scent();

    } else if (!last_known_pos.is_null()) {
        AStarPathFinder pf(map, mobile->get_pos(), last_known_pos);
        list<Position> path = pf.get_path();
        if (path.size() == 0) {

            //mob cant get to player, so give up
            last_known_pos = Position::null_position();
            return;
        }

        list<Position>::iterator i = path.begin();
        i++;

        new_pos = Position(*i);
    }

    //check here since AStarPathFinder doesnt take into account other mobs when
    //calculating the path
    if (map->is_walkable(new_pos)) {
        mobile->set_pos(new_pos);
    }
}

bool ScentMovementStrategy::can_move() {
    detect_last_known_pos();
    return !last_known_pos.is_null() || can_follow_scent();
}

bool ScentMovementStrategy::can_follow_scent() {
    return !adj_pos_with_strongest_scent().is_null();
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

Position ScentMovementStrategy::adj_pos_with_strongest_scent(){
    vector<Position> adj_positions = mobile->get_pos().adjacent_positions();
    Position highest_scent_pos = Position::null_position();
    int highest_scent = -1;

    for (unsigned i = 0; i < adj_positions.size(); i++) {
        Position current = adj_positions.at(i);

        Tile* t;
        if ((t = map->tile_for(current))) {
            if (t->get_scent() > highest_scent) {
                highest_scent = t->get_scent();
                highest_scent_pos = current;
            }
        }
    }

    return highest_scent_pos;
}
