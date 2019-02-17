#ifndef INVENTORY_PANEL_H
#define INVENTORY_PANEL_H

#include <sstream>
#include <ncurses.h>
#include <vector>

#include "../item.h"

namespace UI {
    class InventoryPanel {
        private:
            WINDOW* window;
            int width;
            int height;

        public:
            InventoryPanel(WINDOW* window, int width, int height);
            virtual ~InventoryPanel();

            void render(vector<Item*> items);
            void render_selection_dialog(vector<Item*> items);
    };

}

#endif /* INVENTORY_PANEL_H */
