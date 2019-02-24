#include "engine.h"

Engine::Engine(string map_list_path) {
    this->map_list = new MapList(new string(map_list_path));
    this->map = map_list->get_current_map();
    this->player = new Player(map);
    this->map->set_player(player);
    add_level_entry_msg();
    this->state = NEUTRAL;
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

    start_color();
    init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);

    int height, width;
    getmaxyx(stdscr, height, width);
    std::map<string, int> sizes = UI::PanelSizeCalculator(width, height).get_sizes();

    WINDOW* modal_msg_window = newwin(sizes["map_height"] - 2, sizes["map_width"] - 2, 1, sizes["info_width"] + 1);
    modal_message_panel = new UI::ModalMessagePanel(
        modal_msg_window,
        sizes["map_width"] - 2,
        sizes["map_height"] - 2
    );

    message_panel = new UI::MessagePanel(
        newwin(sizes["msg_height"], sizes["map_width"] + sizes["info_width"], sizes["map_height"], 0),
        sizes["map_width"] + sizes["info_width"],
        sizes["msg_height"]
    );

    map_panel = new UI::MapPanel(
        newwin(sizes["map_height"], sizes["map_width"], 0, sizes["info_width"]),
        sizes["map_width"],
        sizes["map_height"],
        this->player,
        this->map
    );

    info_panel = new UI::InfoPanel(
        newwin(sizes["map_height"], sizes["info_width"], 0, 0)
    );

    inventory_panel = new UI::InventoryPanel(
        newwin(sizes["inv_height"], sizes["inv_width"], sizes["inv_y"], sizes["inv_x"]),
        sizes["inv_height"],
        sizes["inv_width"]
    );


    refresh();
}

void Engine::teardown_curses() {
    endwin();
}

void Engine::render() {
    this->map_panel->render();
    this->message_panel->render();
    this->info_panel->render(*this->player);
    doupdate();
}

bool Engine::handle_keypress(int key) {
    bool turn_taken = true;
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
            state = FIRE;
            turn_taken = false;
            break;
        case (int)'i':
            state = VIEW_INVENTORY;
            turn_taken = false;
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
                    game_over_won();
                }
            }
            break;
        case (int)'w':
            state = WIELD;
            turn_taken = false;
            break;

        case (int)'q':
            main_loop_done = true;
            turn_taken = true;
            break;

        default:
            turn_taken = false;
    }
    return turn_taken;
}

void Engine::do_open() {
    Position target_pos = get_adjacent_position_from_user();

    if (!target_pos.is_null()) {
        player->open(target_pos);
    }
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

    ViewportCalculator vpc(
        map_panel->get_width() - 2,
        map_panel->get_height() - 2,
        player->get_pos(),
        map
    );
    int y = player->get_pos().get_y() - vpc.get_y_offset() + 1;
    int x = player->get_pos().get_x() - vpc.get_x_offset() + 1;

    curs_set(1);


    bool done = false;
    while (!done) {
        map_panel->move_cursor(x, y);
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

void Engine::start_next_level() {
    map = map_list->goto_next_map();
    player->set_map(map);
    map->set_player(player);
    map_panel->set_map(map);
    add_level_entry_msg();
}

void Engine::main_loop() {
    setup_curses();

    map->update_visibility_from(player->get_pos());
    render();

    main_loop_done = false;
    while(!main_loop_done) {

        switch (state) {
            case NEUTRAL:
                if (detect_player_and_mob_turns())
                    break;

                if (detect_modal_messages())
                    break;

                tick();

                break;
            case PLAYER_TURN:
                render();
                if(handle_keypress(getch())) {
                    state = NEUTRAL;
                    player->turn_taken();
                }
                map->update_visibility_from(player->get_pos());
                break;

            case MOB_TURN:
                do_ai();
                state = NEUTRAL;
                break;

            case VIEW_INVENTORY:
                render();
                inventory_panel->render(player->get_inventory()->get_items());
                doupdate();
                getch();
                state = NEUTRAL;
                break;
            case WIELD:
                do_wield();
                state = NEUTRAL;
                player->turn_taken();
                break;
            case FIRE:
                if (fire_weapon()) {
                    player->turn_taken();
                }
                state = NEUTRAL;
                break;
            case MODAL_MSG:
                render();
                this->modal_message_panel->render(fired_cutscenes);
                doupdate();
                while(getch() != ' ') {}
                for (auto cutscene : fired_cutscenes) {
                    cutscene->fired();
                }
                state = NEUTRAL;
                break;

        }

        if (player->is_dead()) {
            game_over_lost();
        }


    }

    teardown_curses();
}

bool Engine::detect_player_and_mob_turns() {
    //check players turn, set state and break
    if (player->is_turn()) {
        state = PLAYER_TURN;
        return true;
    }

    //check ai turn, set state and break
    vector<Positionable*> mobs = map->get_all_mobiles_by_dist_to_player();
    for (unsigned i = 0; i < mobs.size(); i++) {
        Mobile* current = (Mobile*) mobs.at(i);
        if (current->is_turn()) {
            state = MOB_TURN;
            return true;
        }
    }

    return false;
}

bool Engine::detect_modal_messages() {
    fired_cutscenes = map->get_triggered_cutscenes();
    if (fired_cutscenes.size() > 0) {
        state = MODAL_MSG;
        return true;
    }

    return false;
}

void Engine::tick() {
    map->tick();
    player->tick();

    vector<Positionable*> mobs = map->get_all_mobiles();
    for (unsigned i = 0; i < mobs.size(); i++) {
        Mobile* current = (Mobile*) mobs.at(i);
        current->tick();
    }
}

void Engine::do_ai() {
    vector<Positionable*> mobs = map->get_all_mobiles_by_dist_to_player();
    for (unsigned i = 0; i < mobs.size(); i++) {
        Mobile* current = (Mobile*) mobs.at(i);
        if (current->is_turn()) {
            current->take_turn();
        }

    }
}

void Engine::add_level_entry_msg() {
    MessageLog::add_message("Entering " + *map->get_name());
}

void Engine::game_over_lost() {
    main_loop_done = true;
    MessageLog::add_message("You died!");
}

void Engine::game_over_won() {
    main_loop_done = true;
    MessageLog::add_message("You won!");
}

void Engine::do_wield() {
    vector<Item*> wieldables = player->get_inventory()->get_wieldable_items();

    if (wieldables.empty()) {
        MessageLog::add_message("You have nothing to wield!");
        return;
    }

    inventory_panel->render_selection_dialog(wieldables);
    int key = getch() - 48;
    key--; // we render the items starting from 1, not 0

    if (key < 0 || key > 9 || key > (int)wieldables.size()) {
        MessageLog::add_message("Invalid selection");
        return;
    }

    Item* to_wield = wieldables.at(key);
    player->wield((Weapon*)to_wield);
}
