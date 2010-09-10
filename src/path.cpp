#include "path.h"

Path::Path(Position* p) : Tile(p) {
}

bool Path::is_walkable() {
    return true;
}

string* Path::to_char() {
    return new string("*");
}
