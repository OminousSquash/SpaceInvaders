//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_BULLET_H
#define CMAKESFMLPROJECT_BULLET_H

#include "constants.h"
#include <iostream>

using namespace std;

class Bullet {
private:
    int velocity;
    int direction;
    bool terminated;
public:
    Bullet(int direction) : velocity(constants::BULLET_VELOCITY), direction(direction) {}
};


#endif //CMAKESFMLPROJECT_BULLET_H
