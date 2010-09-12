#include "tile.h"

Tile::Tile(Position* p) {
    position = p;
    visible = false;
}

Tile::~Tile() {
    delete position;
}

Position* Tile::pos() {
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
