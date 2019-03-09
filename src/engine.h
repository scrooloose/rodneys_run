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
#include <map>
#include "item.h"
#include <sstream>
#include "cutscene.h"
#include "colors.h"

#include "./ui/info_panel.h"
#include "./ui/map_panel.h"
#include "./ui/message_panel.h"
#include "./ui/modal_message_panel.h"
#include "./ui/panel_size_calculator.h"
#include "./ui/inventory_panel.h"

using namespace std;

class Engine {
    private:
        enum UIState {
            NEUTRAL,
            PLAYER_TURN,
            MOB_TURN,
            MODAL_MSG,
            VIEW_INVENTORY,
            WIELD,
            USE,
            FIRE
        };

        UIState state;

        bool main_loop_done;
        Player* player;
        Map* map;
        MapList* map_list;

        UI::MessagePanel* message_panel;
        UI::InfoPanel* info_panel;
        UI::MapPanel* map_panel;
        UI::ModalMessagePanel* modal_message_panel;
        UI::InventoryPanel* inventory_panel;

        vector<Cutscene*> fired_cutscenes;

        void render();

        void do_open();
        Position get_adjacent_position_from_user();

        void do_ai();
        void game_over_lost();
        void game_over_won();
        void do_wield();
        void do_use();

        bool fire_weapon();
        Position get_position_from_user();

        bool handle_keypress(int key);
        void add_level_entry_msg();
        void start_next_level();

        bool detect_player_and_mob_turns();
        bool detect_modal_messages();

        void tick();

    public:
        Engine(string map_list_path);
        ~Engine();
        void setup_curses();
        void teardown_curses();
        void main_loop();

};

#endif
