#include "stairs.h"

Tiles::Stairs::Stairs(Position p) : Tile(p) {
}

bool Tiles::Stairs::is_walkable() {
    return true;
}

bool Tiles::Stairs::is_descendable() {
    return true;
}

string Tiles::Stairs::to_char() {
    return string(">");
}
