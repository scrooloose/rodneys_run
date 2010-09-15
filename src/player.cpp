#include "player.h"

Player::Player(Map* map) : Positionable(map->get_starting_pos()) {
    this->map = map;
}

Player::~Player() {
    delete position;
}

void Player::move_to(Position* position) {
    Tile* t = map->tile_for(*position);
    if (t->is_walkable()) {
        set_pos(position);
    }
}

void Player::move_up() {
    move_to(position->up());
}

void Player::move_down() {
    move_to(position->down());
}

void Player::move_left() {
    move_to(position->left());
}

void Player::move_right() {
    move_to(position->right());
}

void Player::move_up_left() {
    move_to(position->up_left());
}

void Player::move_up_right() {
    move_to(position->up_right());
}

void Player::move_down_left() {
    move_to(position->down_left());
}

void Player::move_down_right() {
    move_to(position->down_right());
}

bool Player::move_downstairs() {
    return current_tile()->is_descendable();
}

Tile* Player::current_tile() {
    return map->tile_for(*position);
}

void Player::set_map(Map* m) {
    this->map = m;
    this->position = map->get_starting_pos();
}

void Player::open(Position* target_pos){
    if (!position->is_adjacent(target_pos)) {
        throw new runtime_error("Cannot open non-adjacent tile");
    }

    Tile* target_tile = map->tile_for(*target_pos);
    if (target_tile->is_openable()) {
        target_tile->open();
    }
}

string Player::to_char() {
    return string("@");
}
