#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <vector>

class Inventory {
    private:
        vector<Item*> items;
        Item* find(string item_type);

    public:
        Inventory();

        void add(Item item);
        void remove(string item_type, int quantity);
        bool has_item(string item_type);
        void use_item(string item_type);

        vector<Item*> get_items();

};

#endif
