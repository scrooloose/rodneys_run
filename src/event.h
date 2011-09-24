#ifndef EVENT_H
#define EVENT_H

#include "position.h"
#include <string.h>
#include "positionable.h"

class Event {

    protected:
        Position target_pos;
        string msg;
        Positionable* player;
        bool has_fired;

    public:
        Event(Position target_pos, string msg);
        ~Event();

        void set_player(Positionable* p);

        bool check();
        string get_msg();


};

#endif
