#include "key.h"

Key::Key(int door_id, string name, Position position) : Item(name, "key", 1, "%%", position) {
    this->door_id = door_id;
}

int Key::get_door_id() {
    return door_id;
}

string Key::get_door_id_as_string() {
    char s[20];
    sprintf(s, "%d", door_id);
    return string(s);
}
