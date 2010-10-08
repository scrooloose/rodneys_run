#include "engine.h"

Engine::Engine() {
    this->map_list = new MapList(new string("../maps/"));
    this->map = map_list->get_current_map();
    this->player = new Player(map);
    this->map->set_player(player);
    add_level_entry_msg();

    this->show_inventory = false;
}

Engine::~Engine() {
    delete player;
}

void Engine::setup_curses() {
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);

    calculate_window_sizes();
    map_window = newwin(map_win_height, map_win_width, 0, info_win_width);
    msg_window = newwin(msg_win_height, map_win_width + info_win_width, map_win_height, 0);
    info_window = newwin(map_win_height, info_win_width, 0, 0);
    inv_window = newwin(inv_window_height, inv_window_width, 0, 0);

    refresh();
}

void Engine::teardown_curses() {
    endwin();
}

void Engine::render() {
    render_map();
    render_messages();
    render_info();
    if (show_inventory) {
        render_inv();
        show_inventory = false;
    }
    doupdate();
}

void Engine::render_map() {
    werase(map_window);

    ViewportCalculator vpc(map_win_width - 2, map_win_height - 2, player->get_pos(), map);
    vector<Position> to_render = vpc.contained_positions();

    int x_offset = vpc.get_x_offset();
    int y_offset = vpc.get_y_offset();

    for (unsigned i = 0; i < to_render.size(); i++) {
        Position p = to_render.at(i);
        int xpos = p.get_x() - x_offset + 1;
        int ypos = p.get_y() - y_offset + 1;

        Tile* t = map->tile_for(to_render.at(i));
        if (t->is_visible()) {
            mvwprintw(map_window, ypos, xpos , t->to_char().c_str());
        }

        Item* item = map->item_for(to_render.at(i));
        if (item && map->positions_have_los(item->get_pos(), player->get_pos())) {
            mvwprintw(map_window, ypos, xpos , item->to_char().c_str());
        }

        Mobile* mob = (Mobile*) map->mobile_for(to_render.at(i));
        if (mob && mob->is_visible_from(player->get_pos())) {
            mvwprintw(map_window, ypos, xpos , mob->to_char().c_str());
        }

    }

    int ypos = player->get_pos().get_y() - y_offset + 1;
    int xpos = player->get_pos().get_x() - x_offset + 1;
    mvwprintw(map_window, ypos, xpos, player->to_char().c_str());
    box(map_window, 0, 0);
    wnoutrefresh(map_window);
}

void Engine::render_messages() {
    werase(msg_window);

    vector<string*> messages = MessageLog::latest_messages(msg_win_height - 2);
    for (int i = messages.size()-1; i >= 0; i--) {
        mvwprintw(msg_window, i + 1, 1, messages.at(i)->c_str());
    }
    box(msg_window, 0, 0);
    wnoutrefresh(msg_window);
}

void Engine::render_info() {
    werase(info_window);

    mvwprintw(info_window, 1, 1, "Player Info");
    mvwprintw(info_window, 2, 1, "-----------");

    char health_str[20];
    sprintf(health_str, "Health: %d", player->get_health());
    mvwprintw(info_window, 3, 1, health_str);


    mvwprintw(info_window, 6, 1, "Weapons");
    mvwprintw(info_window, 7, 1, "-----------");
    mvwprintw(info_window, 8, 1, player->get_ranged_weapon()->get_name().c_str());
    mvwprintw(info_window, 9, 2, "Dmg:");
    mvwprintw(info_window, 9, 7, player->get_ranged_weapon()->get_dmg_dice_desc().c_str());
    mvwprintw(info_window, 10, 2, "Rng:");
    mvwprintw(info_window, 10, 7, player->get_ranged_weapon()->get_range_desc().c_str());

    mvwprintw(info_window, 12, 1, player->get_melee_weapon()->get_name().c_str());
    mvwprintw(info_window, 13, 2, "Dmg:");
    mvwprintw(info_window, 13, 7, player->get_melee_weapon()->get_dmg_dice_desc().c_str());

    box(info_window, 0, 0);
    wnoutrefresh(info_window);

}

void Engine::render_inv() {
    werase(inv_window);
    box(inv_window, 0, 0);
    mvwprintw(inv_window, 1, 1, "Inventory:");

    vector<Item*> items = player->get_inventory()->get_items();
    for (unsigned i=0; i < items.size(); i++) {
        Item* current = items.at(i);

        mvwprintw(inv_window, i + 3, 1, current->get_inv_string().c_str());
    }

    wnoutrefresh(inv_window);
}

bool Engine::handle_keypress(int key) {
    bool action_taken = true;
    switch(key) {
        case KEY_LEFT:
            player->move_left();
            break;
        case KEY_RIGHT:
            player->move_right();
            break;
        case KEY_UP:
            player->move_up();
            break;
        case KEY_DOWN:
            player->move_down();
            break;
        case KEY_C1:
        case KEY_END:
            player->move_down_left();
            break;
        case KEY_C3:
        case KEY_NPAGE:
            player->move_down_right();
            break;
        case KEY_A1:
        case KEY_HOME:
            player->move_up_left();
            break;
        case KEY_A3:
        case KEY_PPAGE:
            player->move_up_right();
            break;
        case (int)'f':
            if (!fire_weapon()) {
                action_taken = false;
            }
            break;
        case (int)'i':
            show_inventory = true;
            action_taken = false;
            break;
        case (int)'o':
            do_open();
            break;
        case (int)'.': // fall through to '>'
        case (int)'>':
            if (player->move_downstairs()) {
                if (map_list->has_next_map()) {
                    start_next_level();
                }else{
                    action_taken = false;
                }
            }
            break;

        case (int)'q':
            main_loop_done = true;
            action_taken = true;
            break;

        default:
            action_taken = false;
    }
    return action_taken;
}

Position Engine::get_adjacent_position_from_user() {
    Position player_pos = player->get_pos();

    int key = getch();
    switch(key) {
        case KEY_LEFT:
            return player_pos.left();
            break;
        case KEY_RIGHT:
            return player_pos.right();
            break;
        case KEY_UP:
            return player_pos.up();
            break;
        case KEY_DOWN:
            return player_pos.down();
            break;
        case KEY_C1:
        case KEY_END:
            return player_pos.down_left();
            break;
        case KEY_C3:
        case KEY_NPAGE:
            return player_pos.down_right();
            break;
        case KEY_A1:
        case KEY_HOME:
            return player_pos.up_left();
            break;
        case KEY_A3:
        case KEY_PPAGE:
            return player_pos.up_right();
            break;

        default:
            return Position::null_position();
            break;
    }
}

Position Engine::get_position_from_user() {
    //TODO: fix the mem leak here - many Position*s are created
    Position cursor_pos = player->get_pos();

    ViewportCalculator vpc(map_win_width - 2, map_win_height - 2, player->get_pos(), map);
    int y = player->get_pos().get_y() - vpc.get_y_offset() + 1;
    int x = player->get_pos().get_x() - vpc.get_x_offset() + 1;

    curs_set(1);


    bool done = false;
    while (!done) {
        wmove(map_window, y, x);
        wrefresh(map_window);
        int key = getch();
        switch(key) {
            case KEY_LEFT:
                cursor_pos = cursor_pos.left();
                x--;
                break;
            case KEY_RIGHT:
                cursor_pos = cursor_pos.right();
                x++;
                break;
            case KEY_UP:
                cursor_pos = cursor_pos.up();
                y--;
                break;
            case KEY_DOWN:
                cursor_pos = cursor_pos.down();
                y++;
                break;
            case KEY_C1:
            case KEY_END:
                cursor_pos = cursor_pos.down_left();
                y++;
                x--;
                break;
            case KEY_C3:
            case KEY_NPAGE:
                cursor_pos = cursor_pos.down_right();
                y++;
                x++;
                break;
            case KEY_A1:
            case KEY_HOME:
                cursor_pos = cursor_pos.up_left();
                y--;
                x--;
                break;
            case KEY_A3:
            case KEY_PPAGE:
                cursor_pos = cursor_pos.up_right();
                y--;
                x++;
                break;
            case KEY_B2: //5 on the keypad
            case (int)'f': //add f too since gnome term is so fucking stupid it
                           //doesnt recognise the center of the keypad
                done = true;
                break;

            case 27: //esc
                done = true;
                cursor_pos = Position::null_position();
                break;
        }
    }

    curs_set(0);
    return cursor_pos;
}

bool Engine::fire_weapon() {
    Position target_pos = get_position_from_user();
    if(target_pos.is_null() || !map->mobile_for(target_pos))
        return false;

    return player->attack_with_ranged(target_pos);
}

void Engine::do_open() {
    Position target_pos = get_adjacent_position_from_user();

    if (!target_pos.is_null()) {
        player->open(target_pos);
    }
}

void Engine::start_next_level() {
    map = map_list->goto_next_map();
    player->set_map(map);
    map->set_player(player);
    add_level_entry_msg();
}

void Engine::main_loop() {
    int key;

    setup_curses();

    map->update_visibility_from(player->get_pos());
    render();

    main_loop_done = false;
    while(!main_loop_done) {
        bool player_had_turn = false;

        if (player->tick()) {

            bool action_taken = false;
            while (!action_taken) {
                key = getch();
                action_taken = handle_keypress(key);

                if (!action_taken) {
                    render();
                }
            }

            map->update_visibility_from(player->get_pos());
            player_had_turn = true;
        }

        do_ai();

        if (player->is_dead()) {
            game_over();
            main_loop_done = true;
        }

        if (player_had_turn) {
            render();
        }
    }

    teardown_curses();
}

void Engine::do_ai() {
    vector<Positionable*> mobs = map->get_all_mobiles_by_dist_to_player();
    for (unsigned i = 0; i < mobs.size(); i++) {
        Mobile* current = (Mobile*) mobs.at(i);
        current->tick();
    }
}

void Engine::add_level_entry_msg() {
    MessageLog::add_message("Entering " + *map->get_name());
}

void Engine::game_over() {
    MessageLog::add_message("You died!");
}

void Engine::calculate_window_sizes() {
    int height, width;
    getmaxyx(stdscr, height, width);

    msg_win_height = 10;
    info_win_width = 20;

    if (height < 30) {
        msg_win_height = 5;
    }

    map_win_width = width - info_win_width;
    if (map_win_width % 2 == 0) {
        map_win_width--;
    }
    if (map_win_width > 79) {
        map_win_width = 79;
    }

    map_win_height = height - msg_win_height;
    if (map_win_height % 2 == 0) {
        map_win_height--;
    }
    if (map_win_height > 37) {
        map_win_height = 37;
    }

    inv_window_width = 30;
    inv_window_height = 20;
}
