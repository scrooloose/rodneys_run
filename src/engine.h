#ifndef ENGINE_H
#define ENGINE_H

#include "player.h"
#include "map.h"
#include "map_parser.h"
#include "map_list.h"
#include "position.h"
#include <ncurses.h>

class Engine {
    private:
        Player* player;
        Map* map;
        MapList* map_list;

    public:
        Engine();
        ~Engine();
        void setup_curses();
        void teardown_curses();
        void render();
        bool handle_keypress(int key);
        void main_loop();
        void start_next_level();
        Position* get_adjacent_position_from_user();
        void do_open();

};

#endif
