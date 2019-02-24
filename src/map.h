#ifndef MAP_H
#define MAP_H

#include "position.h"
#include "tiles/tile.h"
#include "positionable.h"
#include <vector>
#include <string>
#include "message_log.h"
#include "position_exception.h"
#include "proximity_sorter.h"
#include "item.h"
#include "map_grid.h"
#include "cutscene.h"

using namespace std;
using namespace Tiles;

class Map {
    private:
        MapGrid<Tile> tiles;
        MapGrid<Positionable> mobiles;
        MapGrid<Item> items;
        MapGrid<Cutscene> cutscenes;

        int width;
        int height;
        Position* starting_pos;
        string* name;
        Positionable* player;
        int current_tick;

        void resize_map(int width, int height);
        void update_player_scent();

    public:
        Map(int width, int height);
        ~Map();

        Tile* tile_for(const Position& p);
        Positionable* mobile_for(const Position& p);
        Item* item_for(const Position& p);
        Cutscene* cutscene_for(const Position& p);

        int get_width();
        int get_height();


        void set_starting_pos(const Position& p);
        Position* get_starting_pos();

        void add_tile(Tile* t);
        void add_mobile(Positionable* m);
        void add_item(Item* i);
        void add_cutscene(Cutscene* e);
        Item* remove_item(const Position& p);

        //get all cutscenes triggered this tick
        vector<Cutscene*> get_triggered_cutscenes();

        vector<Tile*> get_all_tiles();
        vector<Positionable*> get_all_mobiles();
        vector<Positionable*> get_all_mobiles_by_dist_to_player();

        bool positions_have_los(const Position& p1, const Position& p2);
        void update_visibility_from(const Position& p);
        void set_name(string* name);
        string* get_name();
        void set_player(Positionable* p);
        Positionable* get_player();
        bool is_walkable(const Position& p, bool ignore_player, bool ignore_mobiles);
        bool is_walkable(const Position& p);

        void update_mobile_position(Positionable* mob, const Position& old_pos, const Position& new_pos);
        void mobile_killed(Positionable* mob);

        void tick();
};

#endif
