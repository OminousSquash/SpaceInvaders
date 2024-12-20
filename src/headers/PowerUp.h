//
// Created by Varun Srinivasan on 24/11/2024.
//

#ifndef CMAKESFMLPROJECT_POWERUP_H
#define CMAKESFMLPROJECT_POWERUP_H

#include "PowerUpTypes.h"
#include <chrono>
#include <ctime>

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

    void set_x(int new_x) {
        x = new_x;
    }

    void set_y(int new_y) {
        y = new_y;
    }
};

#endif //CMAKESFMLPROJECT_POWERUP_H
