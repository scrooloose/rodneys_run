#ifndef INFO_PANEL_H
#define INFO_PANEL_H

#include <ncurses.h>
#include <list>

#include "../player.h"

namespace UI {
    class InfoPanel {
        private:
            WINDOW* window;

        public:
            InfoPanel(WINDOW* window);

            void render(Player& player);
    };
}

#endif
