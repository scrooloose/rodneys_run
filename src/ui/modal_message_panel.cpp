#include "modal_message_panel.h"

UI::ModalMessagePanel::ModalMessagePanel(WINDOW* window, int width, int height) {
    this->window = window;
    this->width = width;
    this->height = height;
}

UI::ModalMessagePanel::~ModalMessagePanel() {
}

void UI::ModalMessagePanel::render(vector<Cutscene*> fired_cutscenes) {
    werase(window);

    for(unsigned i = 0; i < fired_cutscenes.size(); i++) {
        mvwprintw(window, i, 0, fired_cutscenes[i]->get_msg().c_str());
    }

    mvwprintw(window, height-1, 0, "Hit <space> to continue");

    wnoutrefresh(window);
}
