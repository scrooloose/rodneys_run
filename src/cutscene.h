#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <string.h>
#include <vector>
#include "position.h"
#include "positionable.h"
#include "renderable.h"
#include "colors.h"

class Cutscene : public Positionable, public Renderable {

    protected:
        Position target_pos;
        vector<string*> story_pages;
        bool has_fired;

    public:
        Cutscene(Position target_pos, vector<string*> story_pages);
        ~Cutscene();

        vector<string*> get_story_pages();
        void fired();
        bool get_fired();

        // Renderable functions
        string to_char();
        int color_pair();
};

#endif
