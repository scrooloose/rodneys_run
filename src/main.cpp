#include <ncurses.h>
#include <exception>

#include "player.h"
#include "map.h"
#include "engine.h"

int main() {
    Engine* engine = new Engine();
    engine->main_loop();
    return 0;
}
