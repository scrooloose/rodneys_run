#include "wall.h"

Wall::Wall(Position p) : Tile(p) {
}

bool Wall::is_walkable() {
    return false;
}

string Wall::to_char() {
    return string("#");
}

bool Wall::is_transparent() {
    return false;
}
