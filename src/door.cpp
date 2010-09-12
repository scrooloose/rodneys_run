#include "door.h"

Door::Door(Position* p) : Tile(p) {
    is_open = false;
}

bool Door::is_walkable() {
    return is_open;
}

string* Door::to_char() {
    return new string(is_open ? "'" : "+");
}

bool Door::is_transparent() {
    return is_open;
}

bool Door::is_openable() {
    return true;
}

void Door::open() {
    is_open = !is_open;
}


