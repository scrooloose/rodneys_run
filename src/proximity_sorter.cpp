#include "proximity_sorter.h"

vector<Positionable*>* ProximitySorter::mobiles;
Position* ProximitySorter::reference_pos = NULL;


void ProximitySorter::sort_mobiles(vector<Positionable*>* m, Position* p) {
    reference_pos = p;
    mobiles = m;

    sort(mobiles->begin(), mobiles->end(), ProximitySorter::cmp_manhattan_distances);
}

bool ProximitySorter::cmp_manhattan_distances(Positionable* p1, Positionable* p2) {
    int p1_dist = p1->get_pos().manhattan_distance_to(reference_pos);
    int p2_dist = p2->get_pos().manhattan_distance_to(reference_pos);
    return p1_dist < p2_dist;
}
