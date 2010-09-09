#include "map.h"

Map::Map() {
    tiles.resize(10);
    for (int x = 0; x < 10; x++) {
        tiles[x].resize(10);
        for (int y = 0; y < 10; y++) {
            tiles[x][y] = new Floor(new Position(x,y));
        }
    }

    tiles[2][5] = new Wall(new Position(5, 5));
    tiles[3][5] = new Wall(new Position(5, 5));
    tiles[4][5] = new Wall(new Position(5, 5));
    tiles[5][5] = new Wall(new Position(5, 5));
    tiles[6][5] = new Wall(new Position(5, 5));
    tiles[7][5] = new Wall(new Position(5, 5));

    for (int i = 0; i < 10; i++) {
        tiles[i][0] = new Wall(new Position(i, 0));
        tiles[i][9] = new Wall(new Position(i, 9));
        tiles[0][i] = new Wall(new Position(0, i));
        tiles[9][i] = new Wall(new Position(9, i));
    }
}

int Map::width() {
    //hardcoded for now
    return 10;
}

int Map::height() {
    //hardcoded for now
    return 10;
}

Tile* Map::tile_for(Position* p) {
    return tiles.at(p->get_x()).at(p->get_y());
}
