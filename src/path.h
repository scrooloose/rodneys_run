#ifndef PATH_H
#define PATH_H

#include "tile.h"

class Path : public Tile {
    public:
        Path(Position* p);
        bool is_walkable();
        string to_char();
};

#endif
