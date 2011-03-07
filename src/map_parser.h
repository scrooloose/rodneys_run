#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include "map.h"
#include "tiles/tile.h"
#include "tiles/floor.h"
#include "tiles/wall.h"
#include "tiles/stairs.h"
#include "tiles/door.h"
#include "tiles/empty_tile.h"
#include "map_parsing_exception.h"

#include "mobile.h"
#include "zombie.h"

#include "item.h"

#include "map_meta_inf_parser.h"


using namespace std;

class MapParser {
    private:
        string* fname;
        Map* map;

        ifstream* open_map_file();

        void parse_meta_inf();
        string get_meta_inf_file_name();

    public:
        MapParser(string* fname);
        ~MapParser();

        static Map* parse_file(string* fname);

        Map* parse();
        Tile* tile_for(char c, Position p);
        int find_width();
        int find_height();


};

#endif
