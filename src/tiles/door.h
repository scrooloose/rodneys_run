#ifndef DOOR_H
#define DOOR_H

#include "tile.h"

namespace Tiles {

    class Door : public Tile {
        private:
            bool is_open;

            int door_id;
            string name;
            bool locked;

        public:
            Door(Position p);
            Door(Position p, int door_id, string name);

            bool is_walkable();
            string to_char();
            int color_pair();
            bool is_transparent();

            bool is_openable();
            void open();

            bool is_locked();
            void set_locked(bool locked);
            int get_door_id();
            string get_name();
    };

}

#endif
