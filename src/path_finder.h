#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "map.h"
#include "node.h"
#include "position.h"
#include <vector>
#include <list>

using namespace std;

//finds a path between the 2 given positions using the A-star algorithm
class PathFinder {
    private:
        Map* map;
        Position from_pos;
        Position to_pos;

        vector<Node*> open_list;
        vector<Node*> closed_list;

        bool in_closed_list(Node* n);
        bool in_open_list(Node* n);

        list<Position> reconstruct_path(Node* node);

    public:
        PathFinder(Map* map, const Position& from_pos, const Position& to_pos);
        ~PathFinder();
        list<Position> get_path();
};

#endif
