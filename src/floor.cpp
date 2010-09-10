#include "floor.h"

Floor::Floor(Position* p) : Tile(p) {
}

bool Floor::is_walkable() {
    return true;
}

string* Floor::to_char() {
    return new string(".");
}
