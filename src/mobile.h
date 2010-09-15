#ifndef MOBILE_H
#define MOBILE_H

#include "renderable.h"
#include "positionable.h"
#include "position.h"
#include "map.h"

class Mobile : public IRenderable, public Positionable {
    protected:
        Map* map;

    public:
        Mobile(Position* p, Map* m);
        ~Mobile();

        bool is_visible_from(Position* p);
};


#endif
