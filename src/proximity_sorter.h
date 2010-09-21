#ifndef PROXIMITY_SORTER_H
#define PROXIMITY_SORTER_H

#include "positionable.h"
#include "position.h"
#include <vector>
#include <algorithm>

class ProximitySorter {
    private:
        static vector<Positionable*>* mobiles;
        static Position* reference_pos;
        static bool cmp_manhattan_distances(Positionable* p1, Positionable* p2);

    public:
        static void sort_mobiles(vector<Positionable*>* mobiles, Position* reference_pos);
};

#endif
