#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <string.h>
#include "position.h"
#include "positionable.h"
#include "renderable.h"

class Cutscene : public Positionable, public Renderable {

    protected:
        Position target_pos;
        string msg;
        Positionable* player;
        bool has_fired;

    public:
        Cutscene(Position target_pos, string msg);
        ~Cutscene();

        void set_player(Positionable* p);

        bool check();
        string get_msg();
        void fired();
        bool get_fired();

        // Renderable functions
        string to_char();
        int color_pair();
};

#endif
