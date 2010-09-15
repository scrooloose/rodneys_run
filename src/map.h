#ifndef MAP_H
#define MAP_H

#include "position.h"
#include "tile.h"
#include "positionable.h"
#include <vector>
#include <string>

using namespace std;

class Map {
    private:
        vector< vector<Tile*> > tiles;
        vector< vector<Positionable*> > mobiles;
        int width;
        int height;
        Position* starting_pos;
        string* name;

        void resize_map(int width, int height);

    public:
        Map(int width, int height);
        ~Map();

        Tile* tile_for(Position p);
        Positionable* mobile_for(Position p);
        int get_width();
        int get_height();
        void add_tile(Tile* t);
        void add_mobile(Positionable* m);
        void set_starting_pos(Position* p);
        Position* get_starting_pos();
        vector<Tile*> get_all_tiles();
        bool positions_have_los(Position* p1, Position* p2);
        void update_visibility_from(Position* p);
        void set_name(string* name);
        string* get_name();

};

#endif
