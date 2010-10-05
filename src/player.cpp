#include "player.h"

Player::Player(Map* map) : Positionable(*map->get_starting_pos()) {
    this->map = map;
    this->health = 100;
    this->turn_timer = new TurnTimer(10);
    this->inventory = new Inventory();
    this->ranged_weapon = new RangedWeapon(2, 7, this, inventory, "rifle_round", map, "Combat Rifle", 4, 7, 5);
    this->melee_weapon = new MeleeWeapon(this, map, "Brass Knuckles", 2, 3, 3);
}

Player::~Player() {
}

void Player::move_to(const Position& position) {
    if (map->mobile_for(position)) {
        attack_with_melee(position);
    } else {
        Tile* t = map->tile_for(position);
        if (t->is_walkable()) {
            set_pos(position);
        }

        pick_up_items();
    }
}

void Player::pick_up_items() {
    Item* item = map->remove_item(get_pos());
    if (item) {
        item->affect_recipient(this);
        MessageLog::add_message(item->get_pickup_msg());

        if (!item->is_instant_usage_item()) {
            inventory->add(item);
        } else {
            delete item;
        }

    }
}

Inventory* Player::get_inventory() {
    return this->inventory;
}

void Player::move_up() {
    move_to(position.up());
}

void Player::move_down() {
    move_to(position.down());
}

void Player::move_left() {
    move_to(position.left());
}

void Player::move_right() {
    move_to(position.right());
}

void Player::move_up_left() {
    move_to(position.up_left());
}

void Player::move_up_right() {
    move_to(position.up_right());
}

void Player::move_down_left() {
    move_to(position.down_left());
}

void Player::move_down_right() {
    move_to(position.down_right());
}

bool Player::move_downstairs() {
    return current_tile()->is_descendable();
}

Tile* Player::current_tile() {
    return map->tile_for(position);
}

void Player::set_map(Map* m) {
    this->map = m;
    this->position = *map->get_starting_pos();
    this->turn_timer->set_remaining_time(1);
}

void Player::open(const Position& target_pos){
    if (!position.is_adjacent(target_pos)) {
        throw new runtime_error("Cannot open non-adjacent tile");
    }

    Tile* target_tile = map->tile_for(target_pos);
    if (target_tile->is_openable()) {

        //TODO: fix the design so this cast isnt needed
        Door* d = (Door*) target_tile;
        if (d->is_locked()) {
            //verify we have the key
            if (inventory->has_key(d->get_door_id())){
                d->set_locked(false);
                d->open();
                MessageLog::add_message("You unlock the " + d->get_name());
            } else {
                MessageLog::add_message("Dont have the key for the " + d->get_name());
            }
        } else {
            target_tile->open();
        }
    }
}

bool Player::attack_with_melee(Position pos) {
    return melee_weapon->attack(pos);
}

bool Player::attack_with_ranged(Position pos) {
    return ranged_weapon->attack(pos);
}

void Player::attacked_by(Mobile* mobile) {
    health -= mobile->get_attack_damage();
    MessageLog::add_message("You were attacked!");
    if (is_dead()) {
        killed();
    }
}

void Player::killed() {
    //do something here like notify some observers
}

bool Player::is_dead() {
    return health <= 0;
}

int Player::get_health() {
    return health;
}

bool Player::tick() {
    return turn_timer->tick();
}

void Player::set_ranged_weapon(RangedWeapon* rw) {
    this->ranged_weapon = rw;
}

RangedWeapon* Player::get_ranged_weapon() {
    return this->ranged_weapon;
}

void Player::set_melee_weapon(MeleeWeapon* mw) {
    this->melee_weapon = mw;
}
MeleeWeapon* Player::get_melee_weapon() {
    return this->melee_weapon;
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100)
        health = 100;
}

string Player::to_char() {
    return string("@");
}
