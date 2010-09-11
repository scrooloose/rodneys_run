#ifndef MAP_LIST_H
#define MAP_LIST_H

#include <glob.h>
#include <vector>
#include "map.h"
#include "map_parser.h"
#include <string>

using namespace std;

class MapList {
    private:
        vector<Map*> maps;
        int current_map_idx;

        vector<string*> map_paths;
        string* map_dir;

        void init_maps();
        void init_map_paths();

    public:
        MapList(string* map_dir);
        ~MapList();

        bool has_next_map();
        bool has_prev_map();

        Map* get_current_map();
        Map* goto_next_map();
        Map* goto_prev_map();

};

#endif
