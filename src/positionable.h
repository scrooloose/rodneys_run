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

        virtual const Position& get_pos();
        virtual void set_pos(const Position& p);
};

#endif
