#ifndef EMPTY_TILE_H
#define EMPTY_TILE_H

#include "tile.h"

class EmptyTile : public Tile {
    public:
        EmptyTile(Position* p);
        bool is_walkable();
        string* to_char();
};

#endif
