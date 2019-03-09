#include "inventory_panel.h"

UI::InventoryPanel::InventoryPanel(WINDOW* window, int width, int height) {
    this->window = window;
    this->width = width;
    this->height = height;
}

UI::InventoryPanel::~InventoryPanel() {
}

void UI::InventoryPanel::render(vector<Item*> items) {
    werase(window);
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "Inventory:");

    for (unsigned i=0; i < items.size(); i++) {
        Item* current = items.at(i);

        mvwprintw(window, i + 3, 1, current->get_inv_string().c_str());
    }

    wnoutrefresh(window);
}

void UI::InventoryPanel::render_selection_dialog(vector<Item*> items) {
    werase(window);
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "Select an item");

    for (unsigned i=1; i <= items.size(); i++) {
        stringstream out;
        out << i;

        Item* current = items.at(i-1);
        mvwprintw(window, i + 2, 1, (out.str() + " - " + current->get_inv_string()).c_str());
    }

    wnoutrefresh(window);
    doupdate();
}
