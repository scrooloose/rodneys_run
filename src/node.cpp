#include "node.h"

Node::Node(Map* map, Tile* tile, Node* parent, Position destination) : destination(destination) {
    this->map = map;
    this->tile = tile;
    this->parent = parent;
    calculate_h();
}

void Node::calculate_h() {
    this->h = destination.manhattan_distance_to(tile->get_pos());
}

int Node::get_f() {
    return g + h;
}

int Node::get_g() {
    return g;
}

int Node::get_h() {
    return h;
}

Tile* Node::get_tile() {
    return tile;
}

Node* Node::get_parent() {
    return parent;
}

void Node::set_g(int g) {
    this->g = g;
}

void Node::set_parent(Node* parent) {
    this->parent = parent;
}

vector<Node*> Node::get_adjacent_nodes() {
    vector<Node*> adj_nodes;
    vector<Position> adj_positions = tile->get_pos().adjacent_positions();
    for (unsigned i = 0; i < adj_positions.size(); i++) {
        Tile* t = map->tile_for(adj_positions.at(i));
        if (map->is_walkable(adj_positions.at(i), true, true)) {
            adj_nodes.push_back(new Node(map, t, this, destination));
        }
    }

    return adj_nodes;
}

bool Node::equals(Node* other) {
    return tile->get_pos().equals(other->tile->get_pos());
}
