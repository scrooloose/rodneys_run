#include "map.h"

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;

    tiles.resize(width);
    for (int x = 0; x < width; x++) {
        tiles[x].resize(height);
    }


}

int Map::get_width() {
    return width;
}

int Map::get_height() {
    return height;
}

Tile* Map::tile_for(Position* p) {
    return tiles.at(p->get_x()).at(p->get_y());
}

void Map::add_tile(Tile* t) {
    Position* p = t->pos();
    tiles[p->get_x()][p->get_y()] = t;
}
