#include "map_list.h"

MapList::MapList(string* map_dir) {
    this->map_dir = map_dir;
    init_map_paths();
    init_maps();
    this->current_map_idx = 0;
}

void MapList::init_map_paths() {
    glob_t glob_data;
    string* glob_str = &map_dir->append("*.map");
    glob(glob_str->c_str(), 0, NULL, &glob_data);

    vector<string*> paths;

    for (unsigned int i = 0; i < glob_data.gl_pathc; i++) {
        string* s = new string(glob_data.gl_pathv[i]);
        paths.push_back(s);
    }

    this->map_paths = paths;
}

void MapList::init_maps(){
    vector<Map*> maps;

    for (int i = 0; i < (int)this->map_paths.size(); i++) {
        Map* m = MapParser::parse_file(this->map_paths[i]);
        maps.push_back(m);
    }

    this->maps = maps;
}

bool MapList::has_next_map() {
    return current_map_idx < ((int)maps.size() - 1);
}

bool MapList::has_prev_map() {
    return current_map_idx > 0;
}

Map* MapList::get_current_map() {
    return this->maps.at(current_map_idx);
}

Map* MapList::goto_next_map() {
    if (!has_next_map()) {
        throw new runtime_error("No next map");
    }

    current_map_idx++;
    return get_current_map();
}

Map* MapList::goto_prev_map() {
    if (!has_prev_map()) {
        throw new runtime_error("No previous map");
    }

    current_map_idx--;
    return get_current_map();
}
