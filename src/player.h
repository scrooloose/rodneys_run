#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "map.h"


class Player {
    private:
        Position* position;
        Map* map;

        void move_to(Position* position);

    public:
        Player(Position* position, Map* map);
        ~Player();

        Position* pos();

        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void move_up_left();
        void move_up_right();
        void move_down_left();
        void move_down_right();
};

#endif
