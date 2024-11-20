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
private:
    void fire_standard();

    void fire_rpg();

public:
    Player() : lives_left(3), is_powered(false), can_fire(false) {
        set_x(0);
        set_y(0);
    }

    void reset() {
        set_x(0);
        set_y(0);
        is_powered = false;
        can_fire = false;
    }

    void hard_reset() {
        lives_left = 3;
        reset();
    }

    void set_x(int newX) {
        this->x = newX + constants::X_OFFSET;
    }

    void set_y(int newY) {
        this->y = newY + constants::Y_OFFSET;
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

    int get_x() {
        return x;
    }

    int get_y() {
        return y;
    }

    int get_lives_left() {
        return lives_left;
    }

    bool get_can_fire() {
        return can_fire;
    }
};


#endif //CMAKESFMLPROJECT_PLAYER_H
