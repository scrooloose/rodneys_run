#include "stairs.h"

Stairs::Stairs(Position* p) : Tile(p) {
}

bool Stairs::is_walkable() {
    return true;
}

bool Stairs::is_descendable() {
    return true;
}

string* Stairs::to_char() {
    return new string(">");
}
