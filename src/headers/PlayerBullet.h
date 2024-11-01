//
// Created by Varun Srinivasan on 01/11/2024.
//

#ifndef CMAKESFMLPROJECT_PLAYERBULLET_H
#define CMAKESFMLPROJECT_PLAYERBULLET_H

#include "constants.h"
#include "directions.h"
#include "Projectile.h"

class PlayerBullet : public Projectile {
public:
    PlayerBullet() : Projectile() {}

    PlayerBullet(int x, int y) : Projectile(x, y) {}

    void on_impact() override {

    }
};

#endif //CMAKESFMLPROJECT_PLAYERBULLET_H
