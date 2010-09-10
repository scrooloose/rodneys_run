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

Map* MapParser::parse() {
    string line;

    ifstream* map_file = open_map_file();

    Map* map = new Map(find_width(), find_height());


    if (map_file->is_open()) {

        int line_no = 0;
        while (!map_file->eof()) {
            getline(*map_file, line);

            for (int i = 0; i < line.size(); i++) {
                map->add_tile(tile_for(line[i], i, line_no));
            }


            line_no++;
        }

        map_file->close();
    }

    return map;
}


Tile* MapParser::tile_for(char c, int x, int y) {
    Position* p = new Position(x, y);
    switch(c) {
        case (int)'+':
            return new Floor(p);
            break;
        case (int)'#':
            return new Wall(p);
            break;

        default:
            throw new MapParsingException("Unknown map character");
            break;
    }

}

int MapParser::find_width() {
    return 20;
}

int MapParser::find_height() {
    return 20;
}
