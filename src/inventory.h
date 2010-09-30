#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include "key.h"
#include <vector>
#include "message_log.h"

class Inventory {
    private:
        vector<Item*> items;
        Item* find(string item_type);
        vector<Key*> find_keys();

    public:
        Inventory();

        void add(Item *item);
        void remove(string item_type, int quantity);
        bool has_item(string item_type);
        void use_item(string item_type);

        bool has_key(int door_id);

        vector<Item*> get_items();

};

#endif
