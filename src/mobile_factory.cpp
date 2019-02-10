#include "mobile_factory.h"

Mobile* MobileFactory::build_zombie(Map* m, const Position& p) {
    Mobile* mob = new Mobile(p, m, 20);
    MovementStrategy* sms = new ScentMovementStrategy(m, mob);
    AI* ai = new MeleeAI(mob, m, sms);
    mob->set_ai(ai);
    mob->set_attack_dice(3, 6, 0);
    mob->set_renderable_char("z");
    mob->set_health(20);
    return mob;
}

Mobile* MobileFactory::build_giant_spider(Map* m, const Position& p) {
    Mobile* mob = new Mobile(p, m, 5);
    MovementStrategy* sms = new ScentMovementStrategy(m, mob);
    AI* ai = new MeleeAI(mob, m, sms);
    mob->set_ai(ai);
    mob->set_attack_dice(2, 4, 0);
    mob->set_renderable_char("S");
    mob->set_health(5);
    return mob;
}
