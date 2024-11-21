//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_SHIELD_H
#define CMAKESFMLPROJECT_SHIELD_H

#include "ShieldComponent.h"
#include <vector>
#include "constants.h"

class Shield {
private:
    std::vector<ShieldComponent> shield_components;
    int x_begin;
public:
    Shield(int x_begin) : shield_components(std::vector<ShieldComponent>()), x_begin(x_begin) {
        create_all_shield_components();
    }

    void create_all_shield_components();

    std::vector<ShieldComponent> &get_shield_components() {
        return shield_components;
    }

    int get_x_begin() {
        return x_begin;
    }
};


#endif //CMAKESFMLPROJECT_SHIELD_H
