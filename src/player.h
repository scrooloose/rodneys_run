#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "positionable.h"
#include "map.h"
#include "renderable.h"
#include "mobile.h"
#include "message_log.h"
#include "turn_timer.h"

#include "ranged_weapon.h"
#include "melee_weapon.h"

#include "item.h"
#include "item_affectee.h"
#include "inventory.h"
#include "tiles/door.h"

#include "cheese.h"

class Player : public Renderable, public Positionable, public ItemAffectee {
    private:
        Map* map;
        int health;
        TurnTimer* turn_timer;

        void move_to(const Position& position);
        void update_weapon_maps();

        RangedWeapon* ranged_weapon;
        MeleeWeapon* melee_weapon;

        Inventory* inventory;

    public:
        Player(Map* map);
        ~Player();

        Tile* current_tile();
        void set_map(Map* m);

        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void move_up_left();
        void move_up_right();
        void move_down_left();
        void move_down_right();
        bool move_downstairs();

        void open(const Position& p);
        bool attack_with_ranged(Position pos);
        bool attack_with_melee(Position pos);
        void attacked_by(Mobile* mobile);
        void killed();
        bool is_dead();
        int get_health();
        void pick_up_items();
        Inventory* get_inventory();

        bool tick();
        bool is_turn();
        void turn_taken();


        void wield(Weapon* weapon);

        void wield(RangedWeapon* rw);
        RangedWeapon* get_ranged_weapon();

        void wield(MeleeWeapon* mw);
        MeleeWeapon* get_melee_weapon();

        //ItemAffectee methods
        void heal(int amount);

        string to_char();

};

#endif
