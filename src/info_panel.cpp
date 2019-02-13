#include "info_panel.h"

InfoPanel::InfoPanel(WINDOW* window) {
    this->window = window;
}

void InfoPanel::render(Player& player) {
    werase(this->window);

    mvwprintw(this->window, 1, 1, "Player Info");
    mvwprintw(this->window, 2, 1, "-----------");

    char health_str[20];
    sprintf(health_str, "Health: %d", player.get_health());
    mvwprintw(this->window, 3, 1, health_str);

    int y = 6;
    if (player.is_holding_weapon()) {
        mvwprintw(this->window, y++, 1, "Weapons");
        mvwprintw(this->window, y++, 1, "-----------");

        if (player.get_ranged_weapon()) {
            mvwprintw(this->window, y++, 1, player.get_ranged_weapon()->get_name().c_str());
            mvwprintw(this->window, y, 2, "Dmg:");
            mvwprintw(this->window, y++, 7, player.get_ranged_weapon()->get_dmg_dice_desc().c_str());
            mvwprintw(this->window, y, 2, "Rng:");
            mvwprintw(this->window, y++, 7, player.get_ranged_weapon()->get_range_desc().c_str());
        }

        if (player.get_melee_weapon()) {
            mvwprintw(this->window, y++, 1, player.get_melee_weapon()->get_name().c_str());
            mvwprintw(this->window, y, 2, "Dmg:");
            mvwprintw(this->window, y++, 7, player.get_melee_weapon()->get_dmg_dice_desc().c_str());
        }

        y += 2;
    }

    if (!player.get_inventory()->is_empty()) {
        mvwprintw(this->window, y++, 1, "Inventory");
        mvwprintw(this->window, y++, 1, "-----------");

        vector<Item*> items = player.get_inventory()->get_items();
        for (unsigned i=0; i < items.size(); i++) {
            Item* current = items.at(i);
            mvwprintw(this->window, y++, 1, current->get_inv_string().c_str());
        }
    }

    box(this->window, 0, 0);
    wnoutrefresh(this->window);
}
