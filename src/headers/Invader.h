//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_INVADER_H
#define CMAKESFMLPROJECT_INVADER_H

#include "constants.h"

class Invader {
private:
    int x;
    int y;
    int position;
    int level;
    int direction;
    int velocity;
    bool alive;
    bool explode;
public:
    Invader(int position, int level) :
            level(level),
            position(position), direction(1),
            velocity(constants::INVADER_VELOCITY),
            alive(true),
            explode(true) {
        convert_x();
        convert_y();
    }

    void convert_x();

    void convert_y();

    void set_x(int new_x) {
        this->x = new_x;
    }

    void set_y(int new_y) {
        this->y = new_y;
    }

    void kill() {
        alive = false;
    }

    void change_direction() {
        if (direction == 1) {
            direction = -1;
        } else {
            direction = 1;
        }
    }

    int get_x() {
        return x;
    }

    int get_y() {
        return y;
    }

    int get_level() {
        return level;
    }

    int get_position() {
        return position;
    }

    int get_direction() {
        return direction;
    }

    int get_velocity() {
        return velocity;
    }

    bool is_alive() {
        return alive;
    }

    bool should_explode() {
        return explode;
    }

    void exploded() {
        explode = false;
    }
};


#endif //CMAKESFMLPROJECT_INVADER_H
