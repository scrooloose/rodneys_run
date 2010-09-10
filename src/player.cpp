#include "player.h"

Player::Player(Position* position, Map* map) {
    this->position = position;
    this->map = map;
}

Player::~Player() {
    delete position;
}

Position* Player::pos() {
    return position;
}

void Player::move_to(Position* position) {
    Tile* t = map->tile_for(position);
    if (t != NULL && t->is_walkable()) {
        this->position = position;
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
