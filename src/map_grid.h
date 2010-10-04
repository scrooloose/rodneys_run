#ifndef MAP_GRID_H
#define MAP_GRID_H

#include <vector>
#include "position.h"

//T must be Positionable
template <class T>
class MapGrid {
    private:
        vector< vector<T*> > map_objs;
        int width;
        int height;

    public:
        MapGrid();
        MapGrid(int width, int height);

        void add(T* t, Position& p);
        T* remove(Position& p);

        T* get(Position& p);
        vector<T*> get_all();

        void resize(int new_width, int new_height);
};

template <class T>
MapGrid<T>::MapGrid() {
}

template <class T>
MapGrid<T>::MapGrid(int width, int height) {
    resize(width, height);
}

template <class T>
void MapGrid<T>::add(T* t, Position& p) {
    map_objs[p.get_x()][p.get_y()] = t;
}

template <class T>
T* MapGrid<T>::get(Position& p) {
    return map_objs.at(p.get_x()).at(p.get_y());
}

template <class T>
vector<T*> MapGrid<T>::get_all() {
    vector<T*> all_map_objs;

    for (unsigned x=0; x < map_objs.size(); x++) {
        for (unsigned y=0; y < map_objs.at(x).size(); y++) {
            T* t = map_objs.at(x).at(y);
            if (t) {
                all_map_objs.push_back(t);
            }
        }
    }

    return all_map_objs;
}

template <class T>
T* MapGrid<T>::remove(Position& p) {
    T* map_obj = get(p);
    if (map_obj) {
        map_objs.at(p.get_x()).at(p.get_y()) = NULL;
    }

    return map_obj;
}

template <class T>
void MapGrid<T>::resize(int new_width, int new_height) {
    this->width = new_width;
    this->height = new_height;

    map_objs.resize(width);
    for (int x = 0; x < width; x++) {
        map_objs.at(x).resize(height);
    }
}

#endif
