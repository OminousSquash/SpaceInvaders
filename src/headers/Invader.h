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
public:
    Invader(int position, int level) : level(level), position(position), direction(1),
                                       velocity(constants::INVADER_VELOCITY) {
        convert_x();
        convert_y();
    }

    void flip_direction();

    void convert_x();

    void convert_y();

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
};


#endif //CMAKESFMLPROJECT_INVADER_H