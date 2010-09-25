#include "inventory.h"

Inventory::Inventory() {
}

void Inventory::add(Item item) {
    Item* existing_item = find(item.get_type());

    if (existing_item) {
        existing_item->add_to_quantity(item.get_quantity());
    } else {
        items.push_back(new Item(item));
    }

}

Item* Inventory::find(string item_type) {
    for (unsigned i = 0; i < items.size(); i++) {
        if (items.at(i)->get_type() == item_type) {
            return items.at(i);
        }
    }

    return NULL;
}

bool Inventory::has_item(string item_type) {
    return find(item_type) != NULL;
}

void Inventory::remove(string item_type, int quantity) {
    Item* item = find(item_type);

    if (!item)
        throw new runtime_error("Item '"+ item_type +"' not in inventory");

    if (item->get_quantity() < quantity)
        throw new runtime_error("Dont have enough of '"+ item_type +"' in inventory");

    if (item->get_quantity() == quantity) {

        for(vector<Item*>::iterator it = items.begin(); it < items.end(); it++) {
            if ((*it)->get_type() == item_type) {
                items.erase(it);
                break;
            }
        }

    } else {
        item->use(quantity);
    }

}

void Inventory::use_item(string item_type) {
    remove(item_type, 1);
}

vector<Item*> Inventory::get_items() {
    return items;
}
