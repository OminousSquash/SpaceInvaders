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
    queue<InvaderBullet *> invader_bullets;
    PlayerBullet *player_bullet;

public:
    Game() : level(0), score(0), player_bullet(nullptr) {}

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

    vector<Invader> get_invaders() {
        return invaders;
    }

    PlayerBullet *get_player_bullet() {
        return player_bullet;
    }

    queue<InvaderBullet *> get_invader_bullets() {
        return invader_bullets;
    }

    void set_player_bullet(PlayerBullet *bullet) {
        player_bullet = bullet;
    }

    void check_player_bullet_bounds() {
        if (player_bullet->get_y() <= 0) {
            delete player_bullet;
            player_bullet = nullptr;
        }
    }
};


#endif //CMAKESFMLPROJECT_GAME_H
