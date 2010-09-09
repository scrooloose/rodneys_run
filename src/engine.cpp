#include "engine.h"

Engine::Engine() {
    setup_curses();
    this->player = new Player(1,1);
}

Engine::~Engine() {
    delete this->player;
}

void Engine::setup_curses() {
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, true);
    refresh();
}

void Engine::teardown_curses() {
    endwin();
}

void Engine::render() {}

void Engine::handle_keypress(int key) {
    switch(key) {
        case KEY_LEFT:
            printw("left");
            break;
        case KEY_RIGHT:
            printw("right");
            break;
        case KEY_UP:
            printw("up");
            break;
        case KEY_DOWN:
            printw("down");
            break;

        default:
            printw("Unknown keypress");
            //throw exception
    }
}
void Engine::main_loop() {
    int key;

    key = getch();
    handle_keypress(key);
    getch();
}
