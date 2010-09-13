#include "engine.h"

Engine::Engine() {
    this->map_list = new MapList(new string("../maps/"));
    this->map = map_list->get_current_map();
    this->player = new Player(map);
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
    map_window = newwin(map_win_height, map_win_width, 0, 0);
    refresh();
}

void Engine::teardown_curses() {
    endwin();
}

void Engine::render() {
    clear();
    wclear(map_window);

    ViewportCalculator vpc(map_win_width - 2, map_win_height - 2, player->pos(), map);
    vector<Position> to_render = vpc.contained_positions();

    int x_offset = vpc.get_x_offset();
    int y_offset = vpc.get_y_offset();

    for (unsigned i = 0; i < to_render.size(); i++) {
        Tile* t = map->tile_for(to_render.at(i));
        if (t->is_visible()) {
            int xpos = t->pos()->get_x() - x_offset + 1;
            int ypos = t->pos()->get_y() - y_offset + 1;
            mvwprintw(map_window, ypos, xpos , t->to_char()->c_str());
        }
    }

    int ypos = player->pos()->get_y() - y_offset + 1;
    int xpos = player->pos()->get_x() - x_offset + 1;
    mvwprintw(map_window, ypos, xpos, "@");

    box(map_window, '|', '-');
    refresh();
    wrefresh(map_window);
}

bool Engine::handle_keypress(int key) {
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
        case (int)'o':
            do_open();
            break;
        case (int)'.': // fall through to '>'
        case (int)'>':
            if (player->move_downstairs()) {
                if (map_list->has_next_map()) {
                    start_next_level();
                }else{
                    return true;
                }
            }
            break;

        case (int)'q':
            return true;
            break;

        default:
            printw("Unknown keypress");
            refresh();
            //throw exception
    }
    return false;
}

Position* Engine::get_adjacent_position_from_user() {
    Position* player_pos = player->pos();

    int key = getch();
    switch(key) {
        case KEY_LEFT:
            return player_pos->left();
            break;
        case KEY_RIGHT:
            return player_pos->right();
            break;
        case KEY_UP:
            return player_pos->up();
            break;
        case KEY_DOWN:
            return player_pos->down();
            break;
        case KEY_C1:
        case KEY_END:
            return player_pos->down_left();
            break;
        case KEY_C3:
        case KEY_NPAGE:
            return player_pos->down_right();
            break;
        case KEY_A1:
        case KEY_HOME:
            return player_pos->up_left();
            break;
        case KEY_A3:
        case KEY_PPAGE:
            return player_pos->up_right();
            break;

        default:
            return NULL;
            break;
    }
}

void Engine::do_open() {
    Position* target_pos = get_adjacent_position_from_user();

    if (target_pos) {
        player->open(target_pos);
    }
}

void Engine::start_next_level() {
    map = map_list->goto_next_map();
    player->set_map(map);
}

void Engine::main_loop() {
    int key;

    setup_curses();

    map->update_visibility_from(player->pos());
    render();

    bool loop_done = false;
    while(!loop_done) {
        key = getch();
        loop_done = handle_keypress(key);
        map->update_visibility_from(player->pos());
        render();
    }

    teardown_curses();
}
