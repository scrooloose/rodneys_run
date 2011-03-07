#ifndef NODE_H
#define NODE_H

#include "tiles/tile.h"
#include "map.h"
#include "position.h"
#include <stdlib.h>

using namespace Tiles;

class Node {
    private:
        Tile* tile;
        Map* map;
        Node* parent;
        vector<Node*> adjacent_nodes;
        Position destination;

        int g;
        int h;

        void calculate_h();

    public:
        Node(Map* map, Tile* tile, Node* parent, Position destination);

        int get_f();
        int get_g();
        int get_h();
        Node* get_parent();
        void set_g(int g);
        void set_h(int h);
        void set_parent(Node* parent);
        Tile* get_tile();

        vector<Node*> get_adjacent_nodes();
        bool equals(Node* other);

};


#endif
