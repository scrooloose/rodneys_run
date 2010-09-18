#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "positionable.h"
#include "map.h"
#include "renderable.h"
#include "mobile.h"
#include "message_log.h"


class Player : public Renderable, public Positionable {
    private:
        Map* map;
        int health;

        void move_to(Position* position);

    public:
        Player(Map* map);
        ~Player();

        Tile* current_tile();
        void set_map(Map* m);

        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void move_up_left();
        void move_up_right();
        void move_down_left();
        void move_down_right();
        bool move_downstairs();

        void open(Position* p);
        void attack(Mobile* mobile);
        void attacked_by(Mobile* mobile);
        void killed();
        bool is_dead();
        int get_health();

        //from IRenderable
        string to_char();

};

#endif
