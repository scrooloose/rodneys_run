#include "engine.h"

Engine::Engine() {
    MapParser* m = new MapParser(new string("test.map"));
    map = m->parse();

    Position* p = new Position(1,1);
    player = new Player(p, map);

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
    refresh();
}

void Engine::teardown_curses() {
    endwin();
}

void Engine::render() {
    clear();
    for (int x = 0; x < map->get_width(); x++) {
        for (int y = 0; y < map->get_height(); y++) {
            Tile* t = map->tile_for(new Position(x,y));
            if (t) {
                mvprintw(y, x, t->to_char()->c_str());
            }
        }
    }
    mvprintw(player->pos()->get_y(), player->pos()->get_x(), "@");
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
void Engine::main_loop() {
    int key;

    setup_curses();

    render();
    bool loop_done = false;
    while(!loop_done) {
        key = getch();
        loop_done = handle_keypress(key);
        render();
    }

    teardown_curses();
}
