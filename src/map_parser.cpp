#include "map_parser.h"

MapParser::MapParser(string* fname) {
    this->fname = fname;
}

MapParser::~MapParser() {
    delete fname;
}

ifstream* MapParser::open_map_file() {
    return new ifstream(fname->c_str());
}

Map* MapParser::parse_file(string* fname) {
    MapParser* mp = new MapParser(fname);
    return mp->parse();
}

Map* MapParser::parse() {
    string line;

    ifstream* map_file = open_map_file();

    Map* map = new Map(find_width(), find_height());

    if (map_file->is_open()) {

        int line_no = 0;
        while (!map_file->eof()) {
            getline(*map_file, line);

            for (int i = 0; i < map->get_width(); i++) {
                char c = ' ';
                if (i < (int)line.length()) {
                    c = line[i];
                }

                Position* p = new Position(i, line_no);
                if (c == '@') {
                    map->set_starting_pos(p);
                }

                Positionable* mob;
                Tile* t;
                if ((mob = mobile_for(c, p, map)) != NULL) {
                    t = tile_for('.', p);
                    map->add_mobile(mob);
                } else {
                    t = tile_for(c, p);
                }

                map->add_tile(t);
            }

            line_no++;
        }

        map_file->close();
    }

    map->set_name(fname);

    return map;
}


Tile* MapParser::tile_for(char c, Position* p) {
    switch(c) {
        case (int)'.':
        case (int)'@':
            return new Floor(p);
            break;
        case (int)'#':
            return new Wall(p);
            break;
        case (int)'*':
            return new Path(p);
            break;
        case (int)'+':
            return new Door(p);
            break;
        case (int)'>':
            return new Stairs(p);
            break;
        case (int)' ':
            return new EmptyTile(p);
            break;

        default:
            throw new MapParsingException("Unknown map character");
            break;
    }

}

Positionable* MapParser::mobile_for(char c, Position* p, Map* m) {
    switch(c) {
        case (int)'z':
            return new Zombie(p, m);
            break;
    }

    return NULL;
}

int MapParser::find_width() {
    ifstream* map_file = open_map_file();
    int longest_line = 0;

    if (map_file->is_open()) {
        while (!map_file->eof()) {
            string line;
            getline(*map_file, line);
            if ((int)line.length() > longest_line) {
                longest_line = line.length();
            }
        }
    }

    return longest_line;
}

int MapParser::find_height() {
    ifstream* map_file = open_map_file();
    int num_lines = 0;

    if (map_file->is_open()) {
        while (!map_file->eof()) {
            string line;
            getline(*map_file, line);
            num_lines++;
        }
    }

    return num_lines;
}
