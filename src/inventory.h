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
        bool has_item(string item_type, int quantity);
        void use_item(string item_type);
        void use_item(Item& item);

        bool has_key(int door_id);
        bool is_empty();

        vector<Item*> get_items();
        vector<Item*> get_wieldable_items();
        vector<Item*> get_usable_items();

};

#endif
