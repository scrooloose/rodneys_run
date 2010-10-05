#ifndef POSITION_H
#define POSITION_H

#include "position_exception.h"
#include <stdlib.h>
#include <vector>

using namespace std;

class Position {
    private:
        int x;
        int y;

        bool are_coords_valid(int x, int y) const ;

    public:
        Position(int x, int y);

        int get_x() const;
        int get_y() const;

        Position* up() const;
        Position* down() const;
        Position* left() const;
        Position* right() const;
        Position* up_left() const;
        Position* up_right() const;
        Position* down_left() const;
        Position* down_right() const;

        vector<Position> positions_between(Position* p) const;
        bool is_adjacent(Position* p) const;
        bool equals(Position* that) const;
        int distance_to(Position* p) const;
        int manhattan_distance_to(Position* p) const;
        vector<Position> adjacent_positions() const;
};

#endif
