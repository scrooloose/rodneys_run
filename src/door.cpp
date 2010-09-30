#include "door.h"

Door::Door(Position* p) : Tile(p) {
    this->is_open = false;
    this->locked = false;
    this->door_id = -1;
}

Door::Door(Position* p, int door_id, string name) : Tile(p) {
    this->door_id = door_id;
    this->name = name;
    this->locked = true;
}

bool Door::is_walkable() {
    return is_open;
}

string Door::to_char() {
    return string(is_open ? "'" : "+");
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

bool Door::is_locked() {
    return locked;
}

void Door::set_locked(bool locked) {
    this->locked = locked;
}

bool Door::get_door_id() {
    return door_id;
}

string Door::get_name() {
    return name;
}

