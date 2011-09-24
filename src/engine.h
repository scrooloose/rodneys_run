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
#include "a_star_path_finder.h"
#include <list>
#include "item.h"
#include <sstream>
#include "event.h"

class Engine {
    private:
        enum UIState {
            NEUTRAL,
            PLAYER_TURN,
            MOB_TURN,
            MODAL_MSG,
            VIEW_INVENTORY,
            WIELD,
            FIRE
        };

        UIState state;

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

        WINDOW* modal_msg_window;

        vector<Event*> fired_events;

        void render();
        void render_map();
        void render_messages();
        void render_modal_messages();
        void render_info();
        void render_inv();
        void render_inventory_selection_dialog(vector<Item*> choices);

        Position get_adjacent_position_from_user();
        Position get_position_from_user();

        void do_open();
        void do_ai();
        void game_over_lost();
        void game_over_won();
        void do_wield();
        bool fire_weapon();

        bool handle_keypress(int key);
        void add_level_entry_msg();
        void calculate_window_sizes();
        void start_next_level();

        bool detect_player_and_mob_turns();
        bool detect_modal_messages();

        void tick();

    public:
        Engine();
        ~Engine();
        void setup_curses();
        void teardown_curses();
        void main_loop();

};

#endif
