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
#include "RPG.h"
#include <queue>

#include <iostream>
#include <vector>

using namespace std;

class Game {
private:
    int level;
    int score;
    Player player;
    vector<Shield> shields;
    vector<Invader> invaders;
    vector<InvaderBullet *> invader_bullets;
    PlayerBullet *player_bullet;

public:
    Game() : level(0), score(0), player_bullet(nullptr),
             invader_bullets(
                     vector<InvaderBullet *>(constants::NUM_INVADER_LEVELS * constants::NUM_INVADERS, nullptr)) {}

    void update_level();

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

    PlayerBullet *get_player_bullet() {
        return player_bullet;
    }

    vector<InvaderBullet *> &get_invader_bullets() {
        return invader_bullets;
    }

    void set_player_bullet(PlayerBullet *bullet) {
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
};


#endif //CMAKESFMLPROJECT_GAME_H
