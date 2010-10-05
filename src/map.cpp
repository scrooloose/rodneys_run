#include "map.h"

Map::Map(int width, int height) {
    resize_map(width, height);
}

Map::~Map() {
    delete name;
    delete starting_pos;
}

void Map::resize_map(int width, int height) {
    this->width = width;
    this->height = height;

    tiles.resize(width, height);
    mobiles.resize(width, height);
    items.resize(width, height);
}

int Map::get_width() {
    return width;
}

int Map::get_height() {
    return height;
}

Tile* Map::tile_for(Position p) {
    return tiles.get(p);
}

Positionable* Map::mobile_for(Position p) {
    return mobiles.get(p);
}

Item* Map::item_for(Position p) {
    return items.get(p);
}

void Map::add_tile(Tile* t) {
    tiles.add(t, t->get_pos());
}

void Map::add_mobile(Positionable* m) {
    mobiles.add(m, m->get_pos());
}

void Map::add_item(Item* i) {
    items.add(i, i->get_pos());
}

Item* Map::remove_item(Position p) {
    return items.remove(p);
}

void Map::set_starting_pos(Position p) {
    this->starting_pos = new Position(p);
}

Position* Map::get_starting_pos() {
    return starting_pos;
}

vector<Tile*> Map::get_all_tiles() {
    return tiles.get_all();
}

vector<Positionable*> Map::get_all_mobiles() {
    return mobiles.get_all();
}

vector<Positionable*> Map::get_all_mobiles_by_dist_to_player() {
    vector<Positionable*> all_mobs = get_all_mobiles();
    ProximitySorter::sort_mobiles(&all_mobs, &player->get_pos());
    return all_mobs;
}

bool Map::positions_have_los(const Position& p1, const Position& p2) {
    vector<Position> positions = p1.positions_between(p2);

    for (unsigned j=0; j < positions.size() - 1; j++) {
        Tile* tile_in_line = tile_for(positions.at(j));
        if (!tile_in_line->is_transparent()) {
            return false;
        }
    }

    return true;
}

void Map::update_visibility_from(const Position& p) {
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
    if (!ignore_player && player->get_pos().equals(position))
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

    mobiles.remove(old_pos);
    mobiles.add(mob, new_pos);
}

void Map::mobile_killed(Positionable* mob) {
    mobiles.remove(mob->get_pos());
}
