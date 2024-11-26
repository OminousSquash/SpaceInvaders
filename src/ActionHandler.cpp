//
// Created by Varun Srinivasan on 01/11/2024.
//

#include "headers/ActionHandler.h"
#include <SFML/Graphics.hpp>
#include "headers/Player.h"
#include "headers/Invader.h"
#include "headers/constants.h"
#include "headers/PlayerBullet.h"
#include "headers/Game.h"
#include <iostream>

void Actions::player_movement(Game &g) {
    Player &p = g.get_player();
    int player_x = p.get_x();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player_x = std::max(0, player_x - 2 * constants::PLAYER_VELOCITY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player_x = std::min(constants::WINDOW_WIDTH - constants::PLAYER_WIDTH,
                            player_x + 2 * constants::PLAYER_VELOCITY);
    }
    p.set_x(player_x);
}

void Actions::invader_movement(std::vector<Invader> &invaders) {
    int direction = invaders[0].get_direction();
    for (Invader &invader: invaders) {
        invader.set_x(invader.get_x() + direction * constants::INVADER_VELOCITY);
    }

    int x_left = invaders[0].get_x();
    int x_right = invaders[constants::NUM_INVADERS - 1].get_x() + constants::INVADER_LENGTH;

    if (direction == constants::RIGHT && x_right >= constants::WINDOW_WIDTH - constants::BUFFER) {
        for (Invader &invader: invaders) {
            invader.set_y(invader.get_y() + constants::INVADER_DROP);
            invader.change_direction();
        }
    } else if (direction == constants::LEFT && x_left <= constants::BUFFER) {
        for (Invader &invader: invaders) {
            invader.set_y(invader.get_y() + constants::INVADER_DROP);
            invader.change_direction();
        }
    }
}

void Actions::player_bullet_movement(Game &g) {
    PlayerBullet *player_bullet = g.get_player_bullet();
    int player_x = g.get_player().get_x();
    int player_y = g.get_player().get_y();
    if (g.is_scatter_bullet_active() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        g.handle_scatter_bullets(1.0 * player_x, 1.0 * player_y);
        g.disable_scatter_bullet();
        return;
    }
    if (player_bullet == nullptr && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player_bullet = new PlayerBullet(player_x + constants::PLAYER_WIDTH / 2, player_y);
        g.set_player_bullet(player_bullet);
    }
    if (player_bullet == nullptr) {
        return;
    }
    int bullet_y = player_bullet->get_y();
    player_bullet->set_y(bullet_y - constants::BULLET_VELOCITY);
    g.check_player_bullet_bounds();
    g.check_player_bullet_shield_collision();
    g.check_player_bullet_invader_collision();
}

void Actions::invader_bullet_movement(Game &g) {
    vector<InvaderBullet *> &invader_bullets = g.get_invader_bullets();
    for (InvaderBullet *&invader_bullet: invader_bullets) {
        if (invader_bullet == nullptr) {
            continue;
        }
        int invader_bullet_y = invader_bullet->get_y();
        invader_bullet->set_y(invader_bullet_y + constants::BULLET_VELOCITY);
        g.check_invader_bullet_bounds(invader_bullet);
    }
    g.check_invader_bullet_collisions();
}

void Actions::restart_game(Game &g) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
//        std::cout << "RESTART HIT" << std::endl;
        g.restart_game();
    }
}

void Actions::scatter_bullet_movement(Game &g) {
    if (g.is_scatter_bullet_active()) return;
    vector<ScatterBullet *> &scatter_bullets = g.get_scatter_bullets();
    for (ScatterBullet *&bullet: scatter_bullets) {
        if (bullet != nullptr) {
            double bullet_x = bullet->get_x();
            double bullet_y = bullet->get_y();
            bullet->set_x(bullet_x + bullet->get_x_vel());
            bullet->set_y(bullet_y - bullet->get_y_vel());
            g.scatter_bullet_bound_check(bullet);
            g.scatter_bullet_detect_invader_collision(bullet);
            g.deactivate_scatter_bullets(bullet);
        }
    }
}

void Actions::power_up_balls_movement(Game &g) {
    vector<PowerUp *> &power_ups = g.get_power_ups();
    if (power_ups.empty()) return;
    for (PowerUp *&p: power_ups) {
        p->set_y(p->get_y() + constants::POWER_UP_FALL_VELOCITY);
        g.check_player_power_up_collision(p);
        g.power_up_bounds_check();
    }
}