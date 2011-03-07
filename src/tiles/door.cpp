#include "door.h"

Tiles::Door::Door(Position p) : Tile(p) {
    this->is_open = false;
    this->locked = false;
    this->door_id = -1;
}

Tiles::Door::Door(Position p, int door_id, string name) : Tile(p) {
    this->door_id = door_id;
    this->name = name;
    this->locked = true;
    this->is_open = false;
}

bool Tiles::Door::is_walkable() {
    return is_open;
}

string Tiles::Door::to_char() {
    return string(is_open ? "'" : "+");
}

bool Tiles::Door::is_transparent() {
    return is_open;
}

bool Tiles::Door::is_openable() {
    return true;
}

void Tiles::Door::open() {
    is_open = !is_open;
}

bool Tiles::Door::is_locked() {
    return locked;
}

void Tiles::Door::set_locked(bool locked) {
    this->locked = locked;
}

int Tiles::Door::get_door_id() {
    return door_id;
}

string Tiles::Door::get_name() {
    return name;
}

