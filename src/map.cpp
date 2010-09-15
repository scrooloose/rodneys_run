#include "map.h"

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    resize_map(width, height);
}

Map::~Map() {
    delete name;
}

void Map::resize_map(int width, int height) {
    tiles.resize(width);
    for (int x = 0; x < width; x++) {
        tiles[x].resize(height);
    }

    mobiles.resize(width);
    for (int x = 0; x < width; x++) {
        mobiles[x].resize(height);
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

Positionable* Map::mobile_for(Position p) {
    return mobiles.at(p.get_x()).at(p.get_y());
}

void Map::add_tile(Tile* t) {
    Position* p = t->get_pos();
    tiles[p->get_x()][p->get_y()] = t;
}

void Map::add_mobile(Positionable* m) {
    Position* p = m->get_pos();
    mobiles[p->get_x()][p->get_y()] = m;
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

bool Map::positions_have_los(Position* p1, Position* p2) {
    vector<Position> positions = p1->positions_between(p2);

    for (unsigned j=0; j < positions.size() - 1; j++) {
        Tile* tile_in_line = tile_for(positions.at(j));
        if (!tile_in_line->is_transparent()) {
            return false;
        }
    }

    return true;
}

void Map::update_visibility_from(Position* p) {
    vector<Tile*> all_tiles = get_all_tiles();

    for (unsigned i=0; i < all_tiles.size(); i++) {
        Tile* current = all_tiles.at(i);
        if (current->is_visible()) continue;

        if (positions_have_los(p, current->get_pos())) {
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
