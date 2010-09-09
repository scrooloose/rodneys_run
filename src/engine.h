#ifndef ENGINE_H
#define ENGINE_H

#include "player.h"
#include "map.h"
#include "position.h"
#include <ncurses.h>

class Engine {
    private:
        Player* player;
        Map* map;

    public:
        Engine();
        ~Engine();
        void setup_curses();
        void teardown_curses();
        void render();
        bool handle_keypress(int key);
        void main_loop();

};

#endif
