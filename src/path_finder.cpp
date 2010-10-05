#include "path_finder.h"

PathFinder::PathFinder(Map* map, const Position& from, const Position& to) : from_pos(from), to_pos(to) {
    this->map = map;

    Node* initial = new Node(map, map->tile_for(from_pos), NULL, to_pos);
    initial->set_g(0);

    open_list.push_back(initial);

}

PathFinder::~PathFinder() {
    vector<Node*>::iterator it;
    for (it = open_list.begin(); it < open_list.end(); it++) {
        delete * it;
    }
    open_list.clear();

    for (it = closed_list.begin(); it < closed_list.end(); it++) {
        delete * it;
    }
    closed_list.clear();
}

list<Position> PathFinder::get_path() {
    while (!open_list.empty()) {

        //get node in open_list with lowest f
        unsigned min_f_idx = 0;
        for (unsigned i = 0; i < open_list.size(); i++) {
            if (open_list.at(i)->get_f() < open_list.at(min_f_idx)->get_f()) {
                min_f_idx = i;
            }
        }
        Node* current = open_list.at(min_f_idx);

        if (current->get_tile()->get_pos().equals(to_pos)) {
            return reconstruct_path(current);
        }

        //remove current node from open and add it to closed
        open_list.erase(open_list.begin() + min_f_idx);
        closed_list.push_back(current);

        //look at all neighbouring nodes
        vector<Node*> adj_nodes = current->get_adjacent_nodes();
        for (unsigned i = 0; i < adj_nodes.size(); i++) {
            Node* neighbour = adj_nodes.at(i);

            if (in_closed_list(neighbour)) {
                continue;
            }

            int tentative_g_score = current->get_g() + 1;
            bool tentative_is_better;

            if (!in_open_list(neighbour)) {
                open_list.push_back(neighbour);
                tentative_is_better = true;
            } else if (tentative_g_score < neighbour->get_g()) {
                tentative_is_better = true;
            } else {
                tentative_is_better = false;
            }

            if (tentative_is_better) {
                neighbour->set_parent(current);
                neighbour->set_g(tentative_g_score);
                //h is set autmomatically
            }

        }

    }

    //not sure how else to signify that no path was found
    list<Position> empty_path;

    return empty_path;
}

bool PathFinder::in_closed_list(Node* n) {
    for (unsigned i = 0; i < closed_list.size(); i++) {
        if (closed_list.at(i)->equals(n)) {
            return true;
        }
    }

    return false;
}

bool PathFinder::in_open_list(Node* n) {
    for (unsigned i = 0; i < open_list.size(); i++) {
        if (open_list.at(i)->equals(n)) {
            return true;
        }
    }

    return false;
}

list<Position> PathFinder::reconstruct_path(Node* node) {
    list<Position> path;

    Node* current = node;
    do {
        path.push_front(current->get_tile()->get_pos());
        current = current->get_parent();

    } while(current);

    return path;
}
