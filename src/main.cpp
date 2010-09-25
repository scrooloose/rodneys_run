#include "engine.h"
#include <iostream>

int main() {
    Engine engine;
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
