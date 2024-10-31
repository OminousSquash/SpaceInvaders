//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H

#include "constants.h"

class Player {
private:
    int lives_left;
    bool is_powered;
    int x;
    int y;
    bool can_fire;
public:
    Player() : lives_left(3), is_powered(false), can_fire(false) {}

    void set_x(int newX) {
        x = newX + constants::X_OFFSET;
    }

    void set_y(int newY) {
        y = newY + constants::Y_OFFSET;
    }

    void set_can_fire() {
        can_fire = !can_fire;
    }

    void set_lives_left(int newLives) {
        lives_left = newLives;
    }

    void set_is_powered() {
        is_powered = !is_powered;
    }
};


#endif //CMAKESFMLPROJECT_PLAYER_H
