#ifndef ENGINE_H
#define ENGINE_H

#include "player.h"
#include <ncurses.h>

class Engine {

    public:
        Engine();
        ~Engine();
        void setup_curses();
        void teardown_curses();
        void render();
        void handle_keypress(int key);
        void main_loop();

    private:
        Player* player;
};

#endif
