#ifndef MODAL_MESSAGE_PANEL_H
#define MODAL_MESSAGE_PANEL_H

#include <ncurses.h>
#include <vector>

#include "../event.h"

namespace UI {
    class ModalMessagePanel {
    private:
        WINDOW* window;
        int width;
        int height;

    public:
        ModalMessagePanel(WINDOW* window, int width, int height);
        virtual ~ModalMessagePanel();

        void render(vector<Event*> fired_events);
    };
}
#endif /* MODAL_MESSAGE_PANEL_H */
