#include "engine.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [level_set_path]" << endl << "  e.g. " << argv[0] << " ../maps" << endl;
        exit(0);
    }

    string map_path(argv[1]);

    if (*map_path.end() != '/')
        map_path.append("/");

    Engine engine(map_path);
    engine.main_loop();
}
