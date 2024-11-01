//
// Created by Varun Srinivasan on 30/10/2024.
//

#include "headers/Invader.h"
#include "headers/constants.h"


void Invader::convert_x() {
    this->x = (position + 1) * constants::INVADER_GAP_SIZE + position * constants::INVADER_LENGTH;
}

void Invader::convert_y() {
    this->y = constants::TOP_GAP + constants::LEVEL_GAP_SIZE * level + constants::INVADER_HEIGHT * level;
}

