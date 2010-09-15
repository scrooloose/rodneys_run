#ifndef WALL_H
#define WALL_H

#include "tile.h"

class Wall : public Tile {
    public:
        Wall(Position* p);
        bool is_walkable();
        string to_char();
        bool is_transparent();
};

#endif
