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
#include "item.h"

class Engine {
    private:
        bool main_loop_done;
        Player* player;
        Map* map;
        MapList* map_list;

        WINDOW* map_window;
        int map_win_width;
        int map_win_height;

        WINDOW* msg_window;
        int msg_win_height;

        WINDOW* info_window;
        int info_win_width;

        WINDOW* inv_window;
        int inv_window_width;
        int inv_window_height;

        void add_level_entry_msg();

        Position* get_position_from_user();
        bool fire_weapon();

        void calculate_window_sizes();

        bool show_inventory;
    public:
        Engine();
        ~Engine();
        void setup_curses();
        void teardown_curses();

        void render();
        void render_map();
        void render_messages();
        void render_info();
        void render_inv();

        bool handle_keypress(int key);
        void main_loop();
        void start_next_level();
        Position* get_adjacent_position_from_user();
        void do_open();
        void do_ai();
        void game_over();

};

#endif
