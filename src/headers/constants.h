//
// Created by Varun Srinivasan on 31/10/2024.
//

#ifndef CMAKESFMLPROJECT_CONSTANTS_H
#define CMAKESFMLPROJECT_CONSTANTS_H

namespace constants {
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 800;
    const int BULLET_VELOCITY = 5;
    const int INVADER_VELOCITY = 0;
    const int START_X = 200;
    const int START_Y = 0;
    const int BASE_HEIGHT = 30;
    const int BASE_WIDTH = 1000;
    const int PLAYER_HEIGHT = 50;
    const int PLAYER_WIDTH = 50;
    const int X_OFFSET = 0;
    const int Y_OFFSET = WINDOW_HEIGHT - BASE_HEIGHT - PLAYER_HEIGHT + 10;
    const int INVADER_GAP_SIZE = 45;
    const int INVADER_LENGTH = 50;
    const int INVADER_HEIGHT = 50;
    const int TOP_GAP = 80;
    const int LEVEL_GAP_SIZE = 10;
    const int FRAME_MOVEMENT = 1;
    const int BULLET_HEIGHT = 15;
}

#endif //CMAKESFMLPROJECT_CONSTANTS_H
