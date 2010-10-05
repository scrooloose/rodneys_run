#ifndef EMPTY_TILE_H
#define EMPTY_TILE_H

#include "tile.h"

class EmptyTile : public Tile {
    public:
        EmptyTile(Position p);
        bool is_walkable();
        bool is_transparent();
        string to_char();
};

#endif
