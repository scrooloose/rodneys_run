#ifndef MAP_H
#define MAP_H

#include "position.h"
#include "tile.h"
#include "positionable.h"
#include <vector>
#include <string>
#include "message_log.h"
#include "position_exception.h"
#include "proximity_sorter.h"
#include "item.h"
#include "map_grid.h"

using namespace std;

class Map {
    private:
        MapGrid<Tile> tiles;
        MapGrid<Positionable> mobiles;
        MapGrid<Item> items;

        int width;
        int height;
        Position* starting_pos;
        string* name;
        Positionable* player;

        void resize_map(int width, int height);

    public:
        Map(int width, int height);
        ~Map();

        Tile* tile_for(Position p);
        Positionable* mobile_for(Position p);
        Item* item_for(Position p);

        int get_width();
        int get_height();


        void set_starting_pos(const Position& p);
        Position* get_starting_pos();

        void add_tile(Tile* t);
        void add_mobile(Positionable* m);
        void add_item(Item* i);
        Item* remove_item(Position p);

        vector<Tile*> get_all_tiles();
        vector<Positionable*> get_all_mobiles();
        vector<Positionable*> get_all_mobiles_by_dist_to_player();

        bool positions_have_los(const Position& p1, const Position& p2);
        void update_visibility_from(const Position& p);
        void set_name(string* name);
        string* get_name();
        void set_player(Positionable* p);
        Positionable* get_player();
        bool is_walkable(Position p, bool ignore_player, bool ignore_mobiles);
        bool is_walkable(Position p);

        void update_mobile_position(Positionable* mob, Position old_pos, Position new_pos);
        void mobile_killed(Positionable* mob);
};

#endif
