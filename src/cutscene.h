#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <string.h>
#include "position.h"
#include "positionable.h"
#include "renderable.h"
#include "colors.h"

class Cutscene : public Positionable, public Renderable {

    protected:
        Position target_pos;
        string msg;
        bool has_fired;

    public:
        Cutscene(Position target_pos, string msg);
        ~Cutscene();

        string get_msg();
        void fired();
        bool get_fired();

        // Renderable functions
        string to_char();
        int color_pair();
};

#endif
