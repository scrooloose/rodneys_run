#include "inventory.h"

Inventory::Inventory() {
}

void Inventory::add(Item* item) {
    if (item->get_type() == "key") {
        items.push_back(item);
        return;
    }

    Item* existing_item = find(item->get_type());

    if (existing_item) {
        existing_item->add_to_quantity(item->get_quantity());
    } else {
        items.push_back(item);
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

vector<Key*> Inventory::find_keys() {
    vector<Key*> keys;

    for (unsigned i = 0; i < items.size(); i++) {
        if (items.at(i)->get_type() == "key") {
            keys.push_back((Key*) items.at(i));
        }
    }

    return keys;
}

bool Inventory::has_item(string item_type) {
    return find(item_type) != NULL;
}

bool Inventory::has_item(string item_type, int quantity) {
    Item* i = find(item_type);
    return i != NULL && i->get_quantity() >= quantity;
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

vector<Item*> Inventory::get_wieldable_items() {
    vector<Item*> to_return;

    for (unsigned i = 0; i < items.size(); i++){
        if (items.at(i)->is_wieldable()) {
            to_return.push_back(items.at(i));
        }
    }

    return to_return;
}

bool Inventory::has_key(int door_id) {
    vector<Key*> keys = find_keys();

    for (unsigned i = 0; i < keys.size(); i++) {
        if (keys.at(i)->get_door_id() == door_id) {
            return true;
        }
    }

    return false;
}
