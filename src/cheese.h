#ifndef MED_KIT_H
#define MED_KIT_H

#include "item.h"
#include "item_affectee.h"
#include "position.h"
#include "message_log.h"

class Cheese : public Item {
    public:
        Cheese(Position p);
        virtual void affect_recipient(ItemAffectee* ia);
        virtual bool is_instant_usage_item();
};

#endif
