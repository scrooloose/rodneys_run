#include "empty_tile.h"

Tiles::EmptyTile::EmptyTile(Position p) : Tile(p) {
}

bool Tiles::EmptyTile::is_walkable() {
    return false;
}

bool Tiles::EmptyTile::is_transparent() {
    return false;
}

string Tiles::EmptyTile::to_char() {
    return string(" ");
}
