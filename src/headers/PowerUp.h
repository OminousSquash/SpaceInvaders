//
// Created by Varun Srinivasan on 24/11/2024.
//

#ifndef CMAKESFMLPROJECT_POWERUP_H
#define CMAKESFMLPROJECT_POWERUP_H

#include "PowerUpTypes.h"

class PowerUp {
private:
    int x;
    int y;
    PowerUpType type;
public:
    PowerUp(int x, int y, PowerUpType type) : x(x), y(y), type(type) {}

    int get_x() {
        return x;
    }

    int get_y() {
        return y;
    }

    PowerUpType get_power_up_type() {
        return type;
    }
};

#endif //CMAKESFMLPROJECT_POWERUP_H
