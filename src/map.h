#ifndef MAP_H
#define MAP_H

#include "position.h"
#include "tile.h"
#include "floor.h"
#include "wall.h"
#include <vector>

class Player;

class Map {
    private:
        vector< vector<Tile*> > tiles;

    public:
        Map();
        ~Map();

        Tile* tile_for(Position* p);
        int width();
        int height();

};

#endif
