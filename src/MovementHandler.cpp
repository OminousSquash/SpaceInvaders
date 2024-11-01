//
// Created by Varun Srinivasan on 01/11/2024.
//

#include "headers/MovementHandler.h"
#include <SFML/Graphics.hpp>
#include "headers/Player.h"
#include "headers/Invader.h"
#include "headers/constants.h"
#include "headers/PlayerBullet.h"
#include "headers/Game.h"
#include <iostream>

void Movement::player_movement(Player &p) {
    int player_x = p.get_x();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player_x = std::max(0, player_x - 2 * constants::FRAME_MOVEMENT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player_x = std::min(constants::WINDOW_WIDTH - constants::PLAYER_WIDTH,
                            player_x + 2 * constants::FRAME_MOVEMENT);
    }
    p.set_x(player_x);
}

void Movement::invader_movement(std::vector<Invader> &invaders) {
    int direction = invaders[0].get_direction();
    if (direction == 1) {
        while (invaders[invaders.size() - 1].get_x() < constants::WINDOW_WIDTH) {
            for (int i = 0; i < invaders.size(); i++) {
                Invader &invader = invaders[i];
                invader.set_x(invader.get_x() + direction * constants::FRAME_MOVEMENT);
            }
        }
    } else if (direction == -1) {
        while (invaders[0].get_x() > 0) {
            for (int i = 0; i < invaders.size(); i++) {
                Invader &invader = invaders[i];
                invader.set_x(invader.get_x() + direction * constants::FRAME_MOVEMENT);
            }
        }
    }
    for (Invader invader: invaders) {
        invader.change_direction();
    }
}

void Movement::player_bullet_movement(Game &g) {
    PlayerBullet *player_bullet = g.get_player_bullet();
    if (player_bullet == nullptr && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        int player_x = g.get_player().get_x();
        int player_y = g.get_player().get_y();
        player_bullet = new PlayerBullet(player_x + constants::PLAYER_WIDTH / 2, player_y);
        g.set_player_bullet(player_bullet);
    }
    if (player_bullet == nullptr) {
        return;
    }
    int bullet_y = player_bullet->get_y();
    player_bullet->set_y(bullet_y - constants::BULLET_VELOCITY);
    g.check_player_bullet_bounds();
}