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
        int width;
        int height;

        void resize_tiles(int width, int height);

    public:
        Map(int width, int height);
        ~Map();

        Tile* tile_for(Position* p);
        int get_width();
        int get_height();
        void add_tile(Tile* t);

};

#endif
