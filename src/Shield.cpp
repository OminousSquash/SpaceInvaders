//
// Created by Varun Srinivasan on 30/10/2024.
//

#include "headers/Shield.h"
#include <iostream>

void Shield::create_all_shield_components() {
    int component_x = x_begin;
    std::vector<int> heights;
    for (int i = 1; i <= ceil(1.0 * constants::NUM_COMPONENTS / 2); i++) {
        heights.push_back(2 * i);
    }
    for (int i = ceil(1.0 * constants::NUM_COMPONENTS / 2) + 1; i < constants::NUM_COMPONENTS; i++) {
        heights.push_back(heights[constants::NUM_COMPONENTS - i - 1]);
    }
    for (int i = 0; i < constants::NUM_COMPONENTS; i++) {
        ShieldComponent sc{component_x,
                           constants::WINDOW_HEIGHT - constants::SHIELD_TO_BASE_GAP,
                           heights[i]};
        component_x += constants::SHIELD_COMPONENT_WIDTH;
        shield_components.push_back(sc);
    }
}
