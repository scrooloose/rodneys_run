#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>

using namespace std;

class Renderable {
    public:
        virtual string to_char() = 0;
};

#endif
