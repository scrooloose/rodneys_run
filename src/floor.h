#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"
#include <string>

using namespace std;

class Floor : public Tile {
    public:
        Floor(Position* p);
        string to_char();
        bool is_walkable();
};

#endif
