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

vector<Positionable*> Map::get_all_mobiles() {
    vector<Positionable*> all_mobs;

    for (unsigned x=0; x < mobiles.size(); x++) {
        for (unsigned y=0; y < mobiles.at(x).size(); y++) {
            Positionable* current = mobiles.at(x).at(y);
            if (current) {
                all_mobs.push_back(current);
            }
        }
    }

    return all_mobs;
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

void Map::set_player(Positionable* p) {
    this->player = p;
}

Positionable* Map::get_player() {
    return this->player;
}

bool Map::is_walkable(Position position) {
    return is_walkable(position, false, false);
}

bool Map::is_walkable(Position position, bool ignore_player, bool ignore_mobiles) {
    MessageLog::add_message("Map: is_walkable");
    if (!ignore_player && player->get_pos()->equals(&position))
        return false;

    if (!ignore_mobiles && mobile_for(position))
        return false;

    return tile_for(position)->is_walkable();
}

void Map::update_mobile_position(Positionable* mob, Position old_pos, Position new_pos) {
    if (mobile_for(new_pos))
        throw new PositionException("Can't move mobile on top of another.");

    if (new_pos.equals(player->get_pos()))
        throw new PositionException("Can't move mobile on top of player.");

    mobiles.at(old_pos.get_x()).at(old_pos.get_y()) = NULL;
    mobiles[new_pos.get_x()][new_pos.get_y()] = mob;
}

void Map::mobile_killed(Positionable* mob) {
    Position* p = mob->get_pos();
    mobiles.at(p->get_x()).at(p->get_y()) = NULL;
    MessageLog::add_message("Mobile killed");
}
