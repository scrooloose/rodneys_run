#include "modal_message_panel.h"

UI::ModalMessagePanel::ModalMessagePanel(WINDOW* window, int width, int height) {
    this->window = window;
    this->width = width;
    this->height = height;
}

UI::ModalMessagePanel::~ModalMessagePanel() {
}

void UI::ModalMessagePanel::render(Cutscene* fired_cutscene) {
    for (auto page : fired_cutscene->get_story_pages()) {
        werase(window);
        mvwprintw(window, 0, 0, page->c_str());
        mvwprintw(window, height-1, 0, "Hit <space> to continue");
        wrefresh(window);
        while(getch() != ' ') {}
    }
}
