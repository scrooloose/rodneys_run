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

Position* Position::up() {
    return new Position(x, y-1);
}

Position* Position::down() {
    return new Position(x, y+1);
}

Position* Position::left() {
    return new Position(x-1, y);
}

Position* Position::right() {
    return new Position(x+1, y);
}

Position* Position::up_left() {
    return new Position(x-1, y-1);
}

Position* Position::up_right() {
    return new Position(x+1, y-1);
}

Position* Position::down_left() {
    return new Position(x-1, y+1);
}

Position* Position::down_right() {
    return new Position(x+1, y+1);
}

bool Position::are_coords_valid(int x, int y) {
    return x >= 0 && y >= 0;
}

bool Position::is_adjacent(Position* p) {
    int x_delta = abs(this->get_x() - p->get_x());
    int y_delta = abs(this->get_y() - p->get_y());

    return x_delta <= 1 && y_delta <= 1;
}
