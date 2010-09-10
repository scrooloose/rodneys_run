#include "empty_tile.h"

EmptyTile::EmptyTile(Position* p) : Tile(p) {
}

bool EmptyTile::is_walkable() {
    return false;
}

string* EmptyTile::to_char() {
    return new string(" ");
}
