//
// Created by Varun Srinivasan on 01/11/2024.
//

#ifndef CMAKESFMLPROJECT_MOVEMENTHANDLER_H
#define CMAKESFMLPROJECT_MOVEMENTHANDLER_H

#include "Player.h"
#include "Invader.h"
#include "PlayerBullet.h"
#include "Game.h"
#include <vector>

namespace Movement {
    void player_movement(Player &player);

    void invader_movement(std::vector<Invader> &invaders);

    void player_bullet_movement(Game &g);

    void invader_bullet_movement(Game &g);
}

#endif //CMAKESFMLPROJECT_MOVEMENTHANDLER_H
