#ifndef MAP_PANEL_H
#define MAP_PANEL_H

#include <ncurses.h>

#include "../viewport_calculator.h"
#include "../mobile.h"
#include "../player.h"
#include "../map.h"
#include "../viewport_calculator.h"

namespace UI {
    class MapPanel {
        private:
            WINDOW* window;
            int width;
            int height;
            Player* player;
            Map* map;

        public:
            MapPanel(WINDOW* window, int width, int height, Player* player, Map* map);

            void render();
            void set_map(Map* map);
    };
}

#endif
