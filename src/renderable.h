#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>
#include "colors.h"

using namespace std;

class Renderable {
    public:
        virtual string to_char() = 0;
        virtual int color_pair();
};

#endif
