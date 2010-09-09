#include "position.h"

Position::Position(int x, int y) {
    if (!are_coords_valid(x, y)) {
        throw new PositionException("Invalid position data");
    }
    this->x = x;
    this->y = y;
}

int Position::get_x() {
    return this->x;
}

int Position::get_y() {
    return this->y;
}

Position* Position::new_position_for(int x, int y) {
    if (are_coords_valid(x, y)) {
        return new Position(x, y);
    }else{
        throw new PositionException("Invalid position");
    }
}

Position* Position::up() {
    return new_position_for(x, y-1);
}

Position* Position::down() {
    return new_position_for(x, y+1);
}

Position* Position::left() {
    return new_position_for(x-1, y);
}

Position* Position::right() {
    return new_position_for(x+1, y);
}

Position* Position::up_left() {
    return new_position_for(x-1, y-1);
}

Position* Position::up_right() {
    return new_position_for(x+1, y-1);
}

Position* Position::down_left() {
    return new_position_for(x-1, y+1);
}

Position* Position::down_right() {
    return new_position_for(x+1, y+1);
}

bool Position::are_coords_valid(int x, int y) {
    return x >= 0 && y >= 0;
}
