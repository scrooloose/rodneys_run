#include "mobile_factory.h"

Mobile* MobileFactory::build_zombie(Map* m, const Position& p) {
    Mobile* mob = new Mobile(p, m, 15);
    MovementStrategy* sms = new ScentMovementStrategy(m, mob);
    AI* ai = new MeleeAI(mob, m, sms);
    mob->set_ai(ai);
    mob->set_attack_dice(3, 6, 0);
    mob->set_renderable_char("z");
    return mob;
}
