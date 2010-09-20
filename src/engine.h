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
#include <stdio.h>
#include "path_finder.h"
#include <list>

class Engine {
    private:
        Player* player;
        Map* map;
        MapList* map_list;

        WINDOW* map_window;
        static const int map_win_width = 69;
        static const int map_win_height = 31;

        WINDOW* msg_window;
        static const int msg_win_height = 10;
        WINDOW* info_window;
        static const int info_win_width = 20;

        void add_level_entry_msg();

    public:
        Engine();
        ~Engine();
        void setup_curses();
        void teardown_curses();
        void render();
        void render_map();
        void render_messages();
        void render_info();
        bool handle_keypress(int key);
        void main_loop();
        void start_next_level();
        Position* get_adjacent_position_from_user();
        void do_open();
        void do_ai();
        void game_over();

};

#endif
