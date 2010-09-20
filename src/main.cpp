#include "engine.h"

int main() {
    Engine engine;
    try {
        engine.main_loop();
    }catch(...){
        engine.teardown_curses();
        throw;
    }
    return 0;
}
