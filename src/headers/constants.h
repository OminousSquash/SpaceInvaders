//
// Created by Varun Srinivasan on 31/10/2024.
//

#ifndef CMAKESFMLPROJECT_CONSTANTS_H
#define CMAKESFMLPROJECT_CONSTANTS_H

namespace constants {
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 800;
    const int BULLET_VELOCITY = 9;
    const int INVADER_VELOCITY = 1;
    const int START_X = 200;
    const int START_Y = 0;
    const int BASE_HEIGHT = 30;
    const int BASE_WIDTH = 1000;
    const int PLAYER_HEIGHT = 50;
    const int PLAYER_WIDTH = 50;
    const int X_OFFSET = 0;
    const int Y_OFFSET = WINDOW_HEIGHT - BASE_HEIGHT - PLAYER_HEIGHT + 10;
    const int INVADER_GAP_SIZE = 30;
    const int INVADER_LENGTH = 30;
    const int INVADER_HEIGHT = 30;
    const int TOP_GAP = 80;
    const int LEVEL_GAP_SIZE = 10;
    const int PLAYER_VELOCITY = 2;
    const int BULLET_HEIGHT = 30;
    const int NUM_INVADERS = 8;
    const int NUM_INVADER_LEVELS = 4;
    const int INVADER_BULLET_THRESHOLD = 9;
    const int LEFT = -1;
    const int RIGHT = 1;
    const int BUFFER = 50;
    const int INVADER_DROP = 10;
    const int SHIELD_COMPONENT_WIDTH = 2;
    const int NUM_SHIELDS = 4;
    const int NUM_SHIELD_COMPONENTS = 75;
    const int SHIELD_GAP = 75;
    const int SHIELD_TO_BASE_GAP = BASE_HEIGHT + PLAYER_HEIGHT + 75;
    const int POWER_UP_RADIUS = 20;
    const int POWER_UP_FALL_VELOCITY = 5;
    const int SCATTER_POWER_DELAY = 5;
    const int BOMB_POWER_DELAY = 5;
    const int INVADER_BULLET_RNG_THRESHOLD = 1e6 + 1;
}

#endif //CMAKESFMLPROJECT_CONSTANTS_H
