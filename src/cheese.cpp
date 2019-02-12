#include "cheese.h"

Cheese::Cheese(Position p) : Item("Cheese", "cheese", 1, "&", p) {
}

void Cheese::affect_recipient(ItemAffectee* ia) {
    MessageLog::add_message("Healed for 30hp");
    ia->heal(30);
}

bool Cheese::is_instant_usage_item() {
    return true;
}
