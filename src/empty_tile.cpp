#include "empty_tile.h"

EmptyTile::EmptyTile(Position p) : Tile(p) {
}

bool EmptyTile::is_walkable() {
    return false;
}

bool EmptyTile::is_transparent() {
    return false;
}

string EmptyTile::to_char() {
    return string(" ");
}
