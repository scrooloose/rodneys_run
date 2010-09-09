#ifndef TILE_H
#define TILE_H

#include "position.h"
#include <string>

using namespace std;

class Tile {
    private:
        Position* position;

    public:
        Tile(Position* p);
        ~Tile();

        Position* pos();
        virtual bool is_walkable() = 0;
        virtual string* to_char() = 0;
};

#endif
