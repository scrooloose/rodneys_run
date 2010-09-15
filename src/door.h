#ifndef DOOR_H
#define DOOR_H

#include "tile.h"

class Door : public Tile {
    private:
        bool is_open;

    public:
        Door(Position* p);

        bool is_walkable();
        string to_char();
        bool is_transparent();

        bool is_openable();
        void open();
};

#endif
