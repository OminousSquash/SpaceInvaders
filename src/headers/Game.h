//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H


#include "Player.h"
#include "PlayerController.h"
#include "Shield.h"
#include "Invader.h"
#include "PlayerBullet.h"
#include "InvaderBullet.h"
#include "PowerUp.h"
#include "ScatterBullet.h"
#include "RPG.h"
#include <queue>

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

class Game {
private:
    int level;
    int score;
    Player player;
    vector<Shield> shields;
    vector<Invader> invaders;
    vector<InvaderBullet *> invader_bullets;
    vector<PowerUp *> power_ups;
    int num_invaders_alive;
    PlayerBullet *player_bullet;
    vector<ScatterBullet *> scatter_bullets;
    RPG *rpg;
    bool scatter_bullet_active;
    bool rpg_active;
    bool game_over;
    std::chrono::time_point<std::chrono::steady_clock> time_of_scatter_power;
    std::chrono::time_point<std::chrono::steady_clock> time_of_rpg_power;
    bool hit_power_up;
public:
    Game() : level(0),
             score(0),
             player_bullet(nullptr),
             invader_bullets(
                     vector<InvaderBullet *>(constants::NUM_INVADER_LEVELS * constants::NUM_INVADERS, nullptr)),
             num_invaders_alive(constants::NUM_INVADERS * constants::NUM_INVADER_LEVELS),
             game_over(false),
             scatter_bullet_active(false),
             power_ups(vector<PowerUp *>()),
             rpg(nullptr),
             rpg_active(false),
             time_of_scatter_power(std::chrono::steady_clock::now()),
             time_of_rpg_power(std::chrono::steady_clock::now()),
             hit_power_up(false) {}

    void update_level();

    void life_lost_reset();

    void set_player(Player p);

    void set_player_controller(PlayerController pc);

    void add_sheild(Shield &sheild);

    void add_invader(Invader &invader);

    void set_all_invaders();

    void set_all_sheilds();

    Player &get_player() {
        return player;
    }

    vector<Invader> &get_invaders() {
        return invaders;
    }

    PlayerBullet *&get_player_bullet() {
        return player_bullet;
    }

    vector<InvaderBullet *> &get_invader_bullets() {
        return invader_bullets;
    }

    void set_player_bullet(PlayerBullet *&bullet) {
        player_bullet = bullet;
    }

    void check_player_bullet_bounds();

    void check_player_bullet_collisions();

    void handle_player_bullet_collision(int idx);

    void handle_score_update(int invader_level);

    void generate_invader_bullets();

    void check_all_bullet_collisions();

    void check_invader_bullet_bounds(InvaderBullet *&invader_bullet);

    void check_invader_bullet_collisions();

    int get_score();

    void hard_reset();

    void cleanup();

    int get_level() {
        return level;
    }

    void hard_cleanup();

    std::vector<Shield> &get_shields() {
        return shields;
    }

    void handle_player_bullet_collision(ShieldComponent &component);

    void check_player_bullet_invader_collision();

    void check_player_bullet_shield_collision();

    void restart_game() {
        game_over = false;
    }

    bool is_game_over() {
        return game_over;
    }

    void set_game_over() {
        game_over = true;
    }

    void check_player_power_up_collision(PowerUp *&p);

    void enable_scatter_bullet() {
        scatter_bullet_active = true;
    }

    void disable_scatter_bullet() {
        scatter_bullet_active = false;
    }

    vector<ScatterBullet *> &get_scatter_bullets() {
        return scatter_bullets;
    }

    bool is_scatter_bullet_active() {
        return scatter_bullet_active;
    }

    void scatter_bullet_bound_check(ScatterBullet *&bullet);

    void scatter_bullet_detect_invader_collision(ScatterBullet *&bullet);

    void scatter_bullet_reflect(ScatterBullet *&bullet);

    void handle_scatter_bullets(double x, double y);

    void deactivate_scatter_bullets(ScatterBullet *&bullet);

    vector<PowerUp *> &get_power_ups() {
        return power_ups;
    }

    void generate_power_ups();

    double get_time_since_last_scatter_power() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - time_of_scatter_power).count();
    }


    double get_time_since_last_rpg_power() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - time_of_rpg_power).count();
    }

    void power_up_bounds_check();

    RPG *&get_rpg() {
        return rpg;
    }

    bool is_rpg_active() {
        return rpg_active;
    }

    void disable_rpg() {
        rpg_active = false;
    }

    void enable_rgp() {
        rpg_active = true;
    }

    void create_rpg(int x, int y) {
        rpg = new RPG(x, y);
    }

    void check_rpg_invader_collisions();

    void check_rpg_bounds();

    void check_rpg_shield_collisions();

    void rpg_explosion(int centre_x, int centre_y);

    bool get_hit_power_up() {
        return hit_power_up;
    }

    void enable_hit_power_up() {
        hit_power_up = true;
    }

    void disable_hit_power_up() {
        hit_power_up = false;
    }
};


#endif //CMAKESFMLPROJECT_GAME_H
