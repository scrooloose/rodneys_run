#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "position.h"
#include <vector>

class Positionable {
    protected:
        Position position;

    public:
        Positionable(Position p);
        ~Positionable();

        virtual Position& get_pos();
        virtual void set_pos(Position p);
};

#endif
