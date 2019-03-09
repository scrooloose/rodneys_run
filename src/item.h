#ifndef ITEM_H
#define ITEM_H

#include "position.h"
#include "positionable.h"
#include "renderable.h"
#include "item_affectee.h"
#include <string>
#include <cstdio>

class Item : public Positionable, public Renderable {
    protected:
        string name;
        string type;
        int quantity;
        string renderable_char;

    public:
        Item(string name, string type, int quantity, string renderable_char, Position position);
        ~Item();

        string get_name();
        string get_type();

        int get_quantity();
        void set_quantity(int q);
        void add_to_quantity(int diff);
        void use(int amount);

        virtual void affect_recipient(ItemAffectee* ia);
        virtual bool is_instant_usage_item();
        virtual bool is_usable();

        virtual bool is_wieldable();

        string get_pickup_msg();
        string get_inv_string();

        string to_char();
        int color_pair();
};
#endif
