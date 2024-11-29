//
// Created by Varun Srinivasan on 31/10/2024.
//

#ifndef CMAKESFMLPROJECT_CONSTANTS_H
#define CMAKESFMLPROJECT_CONSTANTS_H

#include <string>
#include <iostream>

namespace constants {
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 800;
    const int BULLET_VELOCITY = 6;
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
    const int RPG_POWER_DELAY = 10;
    const int INVADER_BULLET_RNG_THRESHOLD = 1e6 - 1e3;
    const int SCATTER_BULLET_HEIGHT = 45;
    const int EXPLOSION_COUNTDOWN = 50;
    const int RPG_BLAST_RADIUS = 100;
    const int RPG_WIDTH = 10;
    const int HITMARKER_LENGTH = 15;
    const int HITMARKER_WIDTH = 15;
    const std::string EXPLOSION_IMAGE_PATH = "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/sprites/Explosion.png";
    const std::string PLAYER_IMAGE_PATH = "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/sprites/Player.png";
    const std::string HITMARKER_IMAGE_PATH = "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/sprites/Hitmarker.png";
    const std::string RPG_IMAGE_PATH = "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/sprites/RPG.png";
    const std::string INVADER_PATH = "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/sprites/Invader.png";
    const std::string ROBOTO_FONT_PATH = "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/SFMLFonts/roboto/Roboto-Bold.ttf";
}

#endif //CMAKESFMLPROJECT_CONSTANTS_H
