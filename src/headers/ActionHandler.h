//
// Created by Varun Srinivasan on 01/11/2024.
//

#ifndef CMAKESFMLPROJECT_ACTIONHANDLER_H
#define CMAKESFMLPROJECT_ACTIONHANDLER_H

#include "Player.h"
#include "Invader.h"
#include "PlayerBullet.h"
#include "Game.h"
#include <vector>

namespace Actions {
    void player_movement(Player &player);

    void invader_movement(std::vector<Invader> &invaders);

    void player_bullet_movement(Game &g);

    void invader_bullet_movement(Game &g);

    void restart_game(Game &g);
}

#endif //CMAKESFMLPROJECT_ACTIONHANDLER_H
