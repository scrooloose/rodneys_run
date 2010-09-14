#include "map.h"

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    resize_tiles(width, height);
}

Map::~Map() {
    delete name;
}

void Map::resize_tiles(int width, int height) {
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

Tile* Map::tile_for(Position p) {
    return tiles.at(p.get_x()).at(p.get_y());
}

void Map::add_tile(Tile* t) {
    Position* p = t->pos();
    tiles[p->get_x()][p->get_y()] = t;
}

void Map::set_starting_pos(Position* p) {
    this->starting_pos = p;
}

Position* Map::get_starting_pos() {
    return starting_pos;
}

vector<Tile*> Map::get_all_tiles() {
    vector<Tile*> all_tiles;

    for (unsigned x=0; x < tiles.size(); x++) {
        for (unsigned y=0; y < tiles.at(x).size(); y++) {
            all_tiles.push_back(tiles.at(x).at(y));
        }
    }

    return all_tiles;
}

void Map::update_visibility_from(Position* p) {
    vector<Tile*> all_tiles = get_all_tiles();

    for (unsigned i=0; i < all_tiles.size(); i++) {
        Tile* current = all_tiles.at(i);
        if (current->is_visible()) continue;

        vector<Position> positions = p->positions_between(current->pos());

        bool sight_blocked = false;
        for (unsigned j=0; j < positions.size() - 1; j++) {
            Tile* tile_in_line = tile_for(positions.at(j));
            if (!tile_in_line->is_transparent()) {
                sight_blocked = true;
            }
        }

        if (!sight_blocked) {
            current->set_visiblity(true);
        }

    }
}

void Map::set_name(string* name) {
    this->name = name;
}

string* Map::get_name() {
    return name;
}
