//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_INVADER_H
#define CMAKESFMLPROJECT_INVADER_H

#include "constants.h"

class Invader {
private:
    int position;
    int level;
    int direction;
    int velocity;
public:
    Invader(int position, int level) : direction(1), velocity(constants::INVADER_VELOCITY) {}

    void flip_direction();
};


#endif //CMAKESFMLPROJECT_INVADER_H
