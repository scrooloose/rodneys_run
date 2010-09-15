#ifndef STAIRS_H
#define STAIRS_H

#include "tile.h"
#include <string>

class Stairs : public Tile {
    public:
        Stairs(Position* p);
        bool is_walkable();
        bool is_descendable();
        string to_char();
};

#endif
