#include "wall.h"

Tiles::Wall::Wall(Position p) : Tile(p) {
}

bool Tiles::Wall::is_walkable() {
    return false;
}

string Tiles::Wall::to_char() {
    return string("#");
}

bool Tiles::Wall::is_transparent() {
    return false;
}
