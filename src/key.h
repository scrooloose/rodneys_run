#ifndef KEY_H
#define KEY_H

#include "item.h"
#include "position.h"
#include <cstdio>

class Key : public Item {
    private:
        int door_id;

    public:
        Key(int door_id, string name, Position position);
        int get_door_id();
        string get_door_id_as_string();

};

#endif
