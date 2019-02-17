#include "map_panel.h"

UI::MapPanel::MapPanel(WINDOW* window, int width, int height, Player* player, Map* map) {
    this->window = window;
    this->height = height;
    this->width = width;
    this->player = player;
    this->map = map;
}

void UI::MapPanel::render() {
    werase(this->window);

    ViewportCalculator vpc(this->width - 2, this->height - 2, this->player->get_pos(), this->map);
    vector<Position> to_render = vpc.contained_positions();

    int x_offset = vpc.get_x_offset();
    int y_offset = vpc.get_y_offset();

    for (unsigned i = 0; i < to_render.size(); i++) {
        Position p = to_render.at(i);
        int xpos = p.get_x() - x_offset + 1;
        int ypos = p.get_y() - y_offset + 1;

        Tile* t = map->tile_for(to_render.at(i));
        if (t->is_visible()) {
            wattron(this->window, COLOR_PAIR(t->color_pair()));
            mvwprintw(this->window, ypos, xpos , t->to_char().c_str());
        }

        Item* item = map->item_for(to_render.at(i));
        if (item && map->positions_have_los(item->get_pos(), player->get_pos())) {
            wattron(this->window, COLOR_PAIR(item->color_pair()));
            mvwprintw(this->window, ypos, xpos , item->to_char().c_str());
        }

        Mobile* mob = (Mobile*) map->mobile_for(to_render.at(i));
        if (mob && mob->is_visible_from(player->get_pos())) {
            wattron(this->window, COLOR_PAIR(RED_ON_BLACK));
            mvwprintw(this->window, ypos, xpos , mob->to_char().c_str());
        }

    }

    int ypos = player->get_pos().get_y() - y_offset + 1;
    int xpos = player->get_pos().get_x() - x_offset + 1;
    wattron(this->window, COLOR_PAIR(WHITE_ON_BLACK));
    mvwprintw(this->window, ypos, xpos, player->to_char().c_str());
    box(this->window, 0, 0);
    wnoutrefresh(this->window);
}

void UI::MapPanel::set_map(Map* map) {
    this->map = map;
}

void UI::MapPanel::move_cursor(int x, int y) {
    wmove(window, y, x);
    wrefresh(window);
}

int UI::MapPanel::get_width() {
    return width;
}

int UI::MapPanel::get_height() {
    return height;
}
