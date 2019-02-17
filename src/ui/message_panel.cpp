#include "message_panel.h"

UI::MessagePanel::MessagePanel(WINDOW* window, int width, int height) {
    this->window = window;
    this->width = width;
    this->height = height;
}

void UI::MessagePanel::render() {
    werase(this->window);

    vector<string*> messages = MessageLog::latest_messages(this->height - 2);
    for (int i = messages.size()-1; i >= 0; i--) {
        mvwprintw(this->window, i + 1, 1, messages.at(i)->c_str());
    }
    box(this->window, 0, 0);
    wnoutrefresh(this->window);
}
