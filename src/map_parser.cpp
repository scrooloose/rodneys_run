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

    map = new Map(find_width(), find_height());

    if (map_file->is_open()) {

        int line_no = 0;
        while (!map_file->eof()) {
            getline(*map_file, line);

            for (int i = 0; i < map->get_width(); i++) {
                char c = ' ';
                if (i < (int)line.length()) {
                    c = line[i];
                }

                Position p(i, line_no);
                map->add_tile(tile_for(c, p));
            }

            line_no++;
        }

        map_file->close();
    }

    parse_meta_inf();

    return map;
}


Tile* MapParser::tile_for(char c, Position p) {
    switch(c) {
        case (int)'.':
            return new Floor(p);
            break;
        case (int)'#':
            return new Wall(p);
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
            throw MapParsingException("Unknown map character:" + string(1, c));
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

string MapParser::get_meta_inf_file_name() {
    string meta_fname(*fname);
    meta_fname.replace(meta_fname.length() - 3, 3, "json");
    return meta_fname;
}

void MapParser::parse_meta_inf() {
    MapMetaInfParser mmip(get_meta_inf_file_name(), map);
    mmip.parse();

    vector<Mobile*> mobs = mmip.get_mobiles();
    for (unsigned i = 0; i < mobs.size(); i++) {
        map->add_mobile(mobs.at(i));
    }

    map->set_name(new string(mmip.get_map_name()));
    map->set_starting_pos(mmip.get_start_position());

    vector<Item*> items = mmip.get_items();
    for (unsigned i = 0; i < items.size(); i++) {
        map->add_item(items.at(i));
    }

    vector<Door*> locked_doors = mmip.get_locked_doors();
    for (unsigned i = 0; i < locked_doors.size(); i++) {
        map->add_tile(locked_doors.at(i));
    }
}
