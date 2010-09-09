#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"
#include <string>

using namespace std;

class Floor : public Tile {
    public:
        Floor(Position* p);
        bool is_walkable();
        string* to_char();
};

#endif
