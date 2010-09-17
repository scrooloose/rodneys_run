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

vector<Position> Position::positions_between(Position* p){
    //using Bresenham's algorithm

    int x1 = this->x;
    int x2 = p->get_x();
    int y1 = this->y;
    int y2 = p->get_y();

    vector<Position> positions;


    signed char ix;
    signed char iy;

    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x = (x2 > x1?(ix = 1, x2 - x1):(ix = -1, x1 - x2)) << 1;
    int delta_y = (y2 > y1?(iy = 1, y2 - y1):(iy = -1, y1 - y2)) << 1;

    positions.push_back(Position(x1, y1));

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error = delta_y - (delta_x >> 1);

        while (x1 != x2)
        {
            if (error >= 0)
            {
                if (error || (ix > 0))
                {
                    y1 += iy;
                    error -= delta_x;
                }
                // else do nothing
            }
            // else do nothing

            x1 += ix;
            error += delta_y;

            positions.push_back(Position(x1, y1));
        }
    }
    else
    {
        // error may go below zero
        int error = delta_x - (delta_y >> 1);

        while (y1 != y2)
        {
            if (error >= 0)
            {
                if (error || (iy > 0))
                {
                    x1 += ix;
                    error -= delta_y;
                }
                // else do nothing
            }
            // else do nothing

            y1 += iy;
            error += delta_x;

            positions.push_back(Position(x1, y1));
        }
    }

    return positions;
}

bool Position::equals(Position* that) {
    return this->x == that->get_x() && this->y == that->get_y();
}

int Position::distance_to(Position* p) {
    vector<Position> positions = positions_between(p);
    return positions.size() - 1;
}
