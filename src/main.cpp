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
    try {
        engine.main_loop();
    } catch(exception* e) {
        engine.teardown_curses();
        cout << "Exception caught: " << e->what() << endl;
    } catch(exception e) {
        engine.teardown_curses();
        cout << "Exception caught: " << e.what() << endl;
    }
    return 0;
}
