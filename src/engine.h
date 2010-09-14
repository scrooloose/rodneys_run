#ifndef ENGINE_H
#define ENGINE_H

#include "player.h"
#include "map.h"
#include "map_parser.h"
#include "map_list.h"
#include "position.h"
#include "viewport_calculator.h"
#include "message_log.h"
#include <ncurses.h>
#include <string.h>

class Engine {
    private:
        Player* player;
        Map* map;
        MapList* map_list;

        WINDOW* map_window;
        static const int map_win_width = 51;
        static const int map_win_height = 21;

        WINDOW* msg_window;

        void add_level_entry_msg();

    public:
        Engine();
        ~Engine();
        void setup_curses();
        void teardown_curses();
        void render();
        void render_map();
        void render_messages();
        bool handle_keypress(int key);
        void main_loop();
        void start_next_level();
        Position* get_adjacent_position_from_user();
        void do_open();

};

#endif
