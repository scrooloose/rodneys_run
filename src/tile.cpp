#include "tile.h"

Tile::Tile(Position* p) {
    position = p;
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
