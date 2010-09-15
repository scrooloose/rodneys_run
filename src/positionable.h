#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "position.h"

class Positionable {
    protected:
        Position* position;

    public:
        Positionable(Position* p);
        ~Positionable();

        Position* get_pos();
        void set_pos(Position* p);
};

#endif
