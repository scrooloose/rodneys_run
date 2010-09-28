#include "map_meta_inf_parser.h"

MapMetaInfParser::MapMetaInfParser(string fname, Map* map) {
    this->fname = fname;
    this->map = map;
}

string MapMetaInfParser::get_file_contents() {
    ifstream inf_file(fname.c_str());

    if (!inf_file.is_open()) {
        throw MapParsingException("Meta inf file: '" + fname + "' doesn't exist.");
    }

    string file_contents, tmp;
    while (!inf_file.eof()) {
        getline(inf_file, tmp);
        file_contents += tmp;
        file_contents += "\n";
    }

    return file_contents;
}

void MapMetaInfParser::parse() {
    Json::Value root;
    Json::Reader reader;
    bool success = reader.parse(get_file_contents(), root);
    if (!success) {
        throw MapParsingException("Failed to parse '" + fname + "' as json");
    }

    parse_mobiles(root);
    parse_map_name(root);
    parse_start_position(root);
    parse_items(root);
}

void MapMetaInfParser::parse_mobiles(Json::Value root) {
    Json::Value mobiles = root["mobiles"];

    for (unsigned i = 0; i < mobiles.size(); i++) {
        Json::Value current = mobiles[i];

        string type = current["type"].asString();
        int xpos  = current["x"].asInt();
        int ypos  = current["y"].asInt();

        this->mobiles.push_back(mob_for(type, xpos, ypos));
    }
}

Mobile* MapMetaInfParser::mob_for(string type, int xpos, int ypos) {
    if (type == "Zombie")
        return new Zombie(new Position(xpos, ypos), map);
    else
        throw MapParsingException("Unrecognised mobile type:" + type);
}

void MapMetaInfParser::parse_map_name(Json::Value root) {
    Json::Value val = root["name"];
    this->map_name = val.asString();
    if (map_name.empty()) {
        throw MapParsingException("Map name missing in: '" + fname + "'");
    }
}

void MapMetaInfParser::parse_start_position(Json::Value root) {
    Json::Value pos = root["start_position"];
    if (pos["x"].empty() || pos["y"].empty()) {
        throw MapParsingException("Invalid start_position in: '" + fname + "'");
    }

    this->start_position = new Position(pos["x"].asInt(), pos["y"].asInt());
}

void MapMetaInfParser::parse_items(Json::Value root) {
    Json::Value items = root["items"];

    for (unsigned i = 0; i < items.size(); i++) {
        Json::Value current = items[i];

        string type = current["type"].asString();
        int quantity  = current["quantity"].asInt();
        int xpos  = current["x"].asInt();
        int ypos  = current["y"].asInt();

        this->items.push_back(item_for(type, quantity, xpos, ypos));
    }
}

Item* MapMetaInfParser::item_for(string type, int quantity, int xpos, int ypos) {
    if (type == "rifle_round")
        return new Item("Rifle round", type, quantity, "=", new Position(xpos, ypos));
    else
        throw MapParsingException("Unrecognised item type:" + type);

}

string MapMetaInfParser::get_map_name() {
    return map_name;
}

vector<Mobile*> MapMetaInfParser::get_mobiles() {
    return mobiles;
}

vector<Item*> MapMetaInfParser::get_items() {
    return items;
}

Position* MapMetaInfParser::get_start_position() {
    return start_position;
}