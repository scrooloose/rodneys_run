#include "med_kit.h"

MedKit::MedKit(Position* p) : Item("Med Kit", "med_kit", 1, "&", p) {
}

void MedKit::affect_recipient(ItemAffectee* ia) {
    MessageLog::add_message("Healed for 30hp");
    ia->heal(30);
}

bool MedKit::is_instant_usage_item() {
    return true;
}
