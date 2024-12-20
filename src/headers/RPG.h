//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_RPG_H
#define CMAKESFMLPROJECT_RPG_H

#include "constants.h"
#include "directions.h"
#include "Projectile.h"

class RPG : public Projectile {
public:
    RPG() : Projectile() {}

    RPG(int x, int y) : Projectile(x, y) {}
};


#endif //CMAKESFMLPROJECT_RPG_H
