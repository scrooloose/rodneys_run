#ifndef MODAL_MESSAGE_PANEL_H
#define MODAL_MESSAGE_PANEL_H

#include <ncurses.h>
#include <vector>

#include "../cutscene.h"

namespace UI {
    class ModalMessagePanel {
    private:
        WINDOW* window;
        int width;
        int height;

    public:
        ModalMessagePanel(WINDOW* window, int width, int height);
        virtual ~ModalMessagePanel();

        void render(vector<Cutscene*> fired_cutscenes);
    };
}
#endif /* MODAL_MESSAGE_PANEL_H */
