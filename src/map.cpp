#include "map.h"

Map::Map(int width, int height) {
    resize_map(width, height);
    current_tick = 0;
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
    cutscenes.resize(width, height);
}

int Map::get_width() {
    return width;
}

int Map::get_height() {
    return height;
}

Tile* Map::tile_for(const Position& p) {
    return tiles.get(p);
}

Positionable* Map::mobile_for(const Position& p) {
    return mobiles.get(p);
}

Item* Map::item_for(const Position& p) {
    return items.get(p);
}

Cutscene* Map::cutscene_for(const Position& p) {
    return cutscenes.get(p);
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

void Map::add_cutscene(Cutscene* e) {
    cutscenes.add(e, e->get_pos());
}

Item* Map::remove_item(const Position& p) {
    return items.remove(p);
}

vector<Cutscene*> Map::get_triggered_cutscenes() {
    vector<Cutscene*> result;

    Cutscene* cutscene = cutscene_for(player->get_pos());
    if (cutscene && !cutscene->get_fired())
        result.push_back(cutscene);

    return result;
}

void Map::set_starting_pos(const Position& p) {
    this->starting_pos = new Position(p);
}

Position* Map::get_starting_pos() {
    return starting_pos;
}

vector<Tile*> Map::get_all_tiles() {
    return tiles.get_all();
}

vector<Tile*> Map::get_all_tiles_in_range(const Position& p, int range) {
    vector<Tile*> result;

    int start_x = p.get_x() - range;
    if (start_x < 0) start_x = 0;

    int end_x = p.get_x() + range;
    if (end_x >= width) end_x = width - 1;

    int start_y = p.get_y() - range;
    if (start_y < 0) start_y = 0;

    int end_y = p.get_y() + range;
    if (end_y >= height) end_y = height - 1;

    for (int x = start_x; x <= end_x; x++) {
        for (int y = start_y; y <= end_y; y++) {
            result.push_back(tiles.get(Position(x, y)));
        }
    }

    return result;
}

vector<Positionable*> Map::get_all_mobiles() {
    return mobiles.get_all();
}

vector<Positionable*> Map::get_all_mobiles_by_dist_to_player() {
    vector<Positionable*> all_mobs = get_all_mobiles();
    ProximitySorter::sort_mobiles(&all_mobs, player->get_pos());
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
    vector<Tile*> all_tiles = get_all_tiles_in_range(p, 20);

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

bool Map::is_walkable(const Position& position) {
    return is_walkable(position, false, false);
}

bool Map::is_walkable(const Position& position, bool ignore_player, bool ignore_mobiles) {
    if (!ignore_player && player->get_pos().equals(position))
        return false;

    if (!ignore_mobiles && mobile_for(position))
        return false;

    return tile_for(position)->is_walkable();
}

void Map::update_mobile_position(Positionable* mob, const Position& old_pos, const Position& new_pos) {
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

void Map::tick() {
    current_tick++;
    update_player_scent();
}

void Map::update_player_scent() {
    Tile* t = tile_for(player->get_pos());
    t->update_scent(current_tick);
}
