//
// Created by Varun Srinivasan on 01/11/2024.
//

#ifndef CMAKESFMLPROJECT_INVADERBULLET_H
#define CMAKESFMLPROJECT_INVADERBULLET_H

#include "Projectile.h"
#include "directions.h"

class InvaderBullet : public Projectile {
public:
    InvaderBullet() : Projectile() {}

    void on_impact() override {

    }
};


#endif //CMAKESFMLPROJECT_INVADERBULLET_H
