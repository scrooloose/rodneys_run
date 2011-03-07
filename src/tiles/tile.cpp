#include "tile.h"

Tiles::Tile::Tile(Position p) : position(p) {
    visible = false;
}

Tiles::Tile::~Tile() {
}

const Position& Tiles::Tile::get_pos() {
    return position;
}

bool Tiles::Tile::is_descendable() {
    return false;
}

bool Tiles::Tile::is_openable() {
    return false;
}

void Tiles::Tile::open() {
    throw new runtime_error("Tiles::Tile::open not implemented");
}

bool Tiles::Tile::is_visible() {
    return visible;
}

void Tiles::Tile::set_visiblity(bool visible) {
    this->visible = visible;
}

bool Tiles::Tile::is_transparent() {
    return true;
}

void Tiles::Tile::update_scent(int new_scent) {
    scent = new_scent;
}
