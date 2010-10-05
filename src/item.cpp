#include "item.h"

Item::Item(string name, string type, int quantity, string renderable_char, Position* position) : Positionable(*position) {
    this->name = name;
    this->type = type;
    this->quantity = quantity;
    this->renderable_char = renderable_char;
}

Item::~Item() {
}

string Item::get_inv_string() {
    if (quantity > 1) {
        char msg[200];
        sprintf(msg, "%d * %s", quantity, name.c_str());
        return string(msg);
    } else {
        return "a " + name;
    }
}

string Item::get_pickup_msg() {
    if (quantity > 1) {
        char msg[200];
        sprintf(msg, "Picked up %d * %s", quantity, name.c_str());
        return string(msg);
    } else {
        return "Picked up a " + name;
    }
}

string Item::to_char() {
    return this->renderable_char;
}

string Item::get_name() {
    return this->name;
}

string Item::get_type() {
    return this->type;
}

int Item::get_quantity() {
    return this->quantity;
}

void Item::set_quantity(int q) {
    if (q < 1) {
        throw new runtime_error("Quantity must be > 0");
    }
    this->quantity = q;
}

void Item::add_to_quantity(int amount) {
    set_quantity(quantity + amount);
}

void Item::use(int amount) {
    set_quantity(quantity - amount);
}

void Item::affect_recipient(ItemAffectee* ia) {
    //let subclasses override and define any actions
}

bool Item::is_instant_usage_item() {
    return false;
}
