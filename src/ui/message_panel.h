#ifndef MESSAGE_PANEL_H
#define MESSAGE_PANEL_H

#include <ncurses.h>
#include <vector>
#include <string>

#include "../message_log.h"

using namespace std;

namespace UI {
    class MessagePanel {
        private:
            WINDOW* window;
            int width;
            int height;

        public:
            MessagePanel(WINDOW* window, int width, int height);

            void render();
    };
}

#endif
