#include "floor.h"

Tiles::Floor::Floor(Position p) : Tile(p) {
}

bool Tiles::Floor::is_walkable() {
    return true;
}

string Tiles::Floor::to_char() {
    return string(".");
}
