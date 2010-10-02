#ifndef ITEM_AFFECTEE_H
#define ITEM_AFFECTEE_H

//An interface to specify all actions an item can take on a subject (probably
//the player).
class ItemAffectee {
    public:
        virtual void heal(int amount) = 0;

};

#endif
