#include "map_meta_inf_parser.h"

MapMetaInfParser::MapMetaInfParser(string fname, Map* map) {
    this->fname = fname;
    this->map = map;
}

MapMetaInfParser::~MapMetaInfParser() {
    delete start_position;
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
    parse_keys(root);
    parse_locked_doors(root);
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
        return new Zombie(Position(xpos, ypos), map);
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

void MapMetaInfParser::parse_keys(Json::Value root) {
    Json::Value keys = root["keys"];

    for (unsigned i = 0; i < keys.size(); i++) {
        Json::Value current = keys[i];

        int door_id  = current["door_id"].asInt();
        string name = current["name"].asString();
        int xpos  = current["x"].asInt();
        int ypos  = current["y"].asInt();

        this->items.push_back(new Key(door_id, name, Position(xpos, ypos)));
    }
}

void MapMetaInfParser::parse_locked_doors(Json::Value root) {
    Json::Value doors = root["locked-doors"];
    for (unsigned i = 0; i < doors.size(); i++) {
        Json::Value current = doors[i];

        int door_id  = current["door_id"].asInt();
        string name = current["name"].asString();
        int xpos  = current["x"].asInt();
        int ypos  = current["y"].asInt();

        this->locked_doors.push_back(new Door(Position(xpos, ypos), door_id, name));
    }
}

Item* MapMetaInfParser::item_for(string type, int quantity, int xpos, int ypos) {
    Position pos(xpos, ypos);

    if (type == "9mm_round")
        return new Item("9mm round", type, quantity, "=", pos);
    else if (type == "shotgun_shell")
        return new Item("Shotgun Shell", type, quantity, "=", pos);
    else if (type == "med_kit")
        return new MedKit(pos);
    else if (type == "pistol")
        return WeaponFactory::build_pistol(map, pos);
    else if (type == "shotgun")
        return WeaponFactory::build_shotgun(map, pos);
    else if (type == "p90")
        return WeaponFactory::build_p90(map, pos);
    else if (type == "lead_pipe")
        return WeaponFactory::build_lead_pipe(map, pos);
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

vector<Door*> MapMetaInfParser::get_locked_doors() {
    return locked_doors;
}

const Position& MapMetaInfParser::get_start_position() {
    return *start_position;
}
