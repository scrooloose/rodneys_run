#include "tile.h"

Tile::Tile(Position p) : position(p) {
    visible = false;
}

Tile::~Tile() {
}

const Position& Tile::get_pos() {
    return position;
}

bool Tile::is_descendable() {
    return false;
}

bool Tile::is_openable() {
    return false;
}

void Tile::open() {
    throw new runtime_error("Tile::open not implemented");
}

bool Tile::is_visible() {
    return visible;
}

void Tile::set_visiblity(bool visible) {
    this->visible = visible;
}

bool Tile::is_transparent() {
    return true;
}

void Tile::update_scent(int new_scent) {
    scent = new_scent;
}
