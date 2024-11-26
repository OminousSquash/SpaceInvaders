//
// Created by Varun Srinivasan on 30/10/2024.
//

#include "headers/Game.h"
#include <ctime>

void Game::update_level() {
    hard_cleanup();
    player.reset();
    set_all_invaders();
    level++;
}

void Game::set_player(Player p) {
    this->player = p;
}

void Game::set_all_invaders() {
    for (int i = 0; i < constants::NUM_INVADER_LEVELS; i++) {
        for (int j = 0; j < constants::NUM_INVADERS; j++) {
            Invader inv(j, i);
            add_invader(inv);
        }
    }
}

void Game::set_all_sheilds() {
    for (int i = 0; i < constants::NUM_SHIELDS; i++) {
        Shield new_shield(
                (i + 1) * constants::SHIELD_GAP +
                i * (constants::NUM_SHIELD_COMPONENTS * constants::SHIELD_COMPONENT_WIDTH));
        shields.push_back(new_shield);
    }
}


void Game::add_invader(Invader &invader) {
    invaders.push_back(invader);
}

void Game::add_sheild(Shield &sheild) {
    shields.push_back(sheild);
}

void Game::check_player_bullet_bounds() {
    if (player_bullet == nullptr) {
        return;
    }
    if (player_bullet->get_y() <= 0) {
        delete player_bullet;
        player_bullet = nullptr;
    }
}

void Game::handle_player_bullet_collision(int idx) {
    Invader &invader = invaders[idx];
    invader.kill();
    num_invaders_alive--;
    if (num_invaders_alive == 0) {
        Game::update_level();
    }
}

void Game::handle_player_bullet_collision(ShieldComponent &component) {
    component.kill_display();
}


void Game::handle_score_update(int invader_level) {
    score += (constants::NUM_INVADER_LEVELS - invader_level) * 10;
}

void Game::check_player_bullet_shield_collision() {
    if (player_bullet == nullptr) {
        return;
    }
    int bullet_x = player_bullet->get_x();
    int bullet_y = player_bullet->get_y() - constants::BULLET_HEIGHT;
    for (int i = 0; i < constants::NUM_SHIELDS; i++) {
        Shield &sheild = shields[i];
        int x_begin = sheild.get_x_begin();
        int x_end = sheild.get_x_begin() + (constants::NUM_SHIELD_COMPONENTS * (constants::SHIELD_COMPONENT_WIDTH));
        if (!(x_begin <= bullet_x && bullet_x <= x_end)) {
            continue;
        }
        for (int j = 0; j < constants::NUM_SHIELD_COMPONENTS; j++) {
            ShieldComponent &sc = sheild.get_shield_components()[j];
            int sc_x = sc.get_x();
            int sc_y = sc.get_y();
            if (sc_x <= bullet_x && bullet_x < sc_x + constants::SHIELD_COMPONENT_WIDTH && sc.is_collidable() &&
                bullet_y >= sc_y && bullet_y <= sc_y + sc.get_height()) {
//                std::cout << "HIT SHIELD COMPONENT: " << sc_x << "," << sc_y << std::endl;
//                std::cout << "BULLET: " << bullet_x << "," << bullet_y << std::endl;
                delete player_bullet;
                player_bullet = nullptr;
                handle_player_bullet_collision(sc);
                return;
            }
        }
    }
}

void Game::check_player_bullet_invader_collision() {
    if (player_bullet == nullptr) {
//        std::cout << "EARLY RETURN" << std::endl;
        return;
    }
    for (int i = 0; i < invaders.size(); i++) {
        Invader &invader = invaders[i];
        int invader_x = invader.get_x();
        int invader_y = invader.get_y();
        int bullet_x = player_bullet->get_x();
        int bullet_y = player_bullet->get_y() - constants::BULLET_HEIGHT;
        if (invader_x <= bullet_x && bullet_x <= invader_x + constants::INVADER_LENGTH
            && invader_y <= bullet_y && bullet_y <= invader_y + constants::INVADER_HEIGHT
            && invader.is_alive()) {
            delete player_bullet;
            player_bullet = nullptr;
            handle_player_bullet_collision(i);
            handle_score_update(invader.get_level());
            return;
        }
    }
}

void Game::generate_invader_bullets() {
    for (int i = 0; i < invaders.size(); i++) {
        Invader &invader = invaders[i];
        srand(time(0));
        int x = rand() % 100;
        if (invader.is_alive() && invader_bullets[i] == nullptr && x >= 50) {
            invader_bullets[i] = new InvaderBullet(invader.get_x() + constants::INVADER_LENGTH / 2,
                                                   invader.get_y() + constants::INVADER_HEIGHT);
        }
    }
}


void Game::check_invader_bullet_bounds(InvaderBullet *&invader_bullet) {
    if (invader_bullet == nullptr)
        return;
    int y = invader_bullet->get_y();
    if (y + constants::BULLET_HEIGHT >= constants::WINDOW_HEIGHT) {
        delete invader_bullet;
        invader_bullet = nullptr;
    }
}

void Game::check_invader_bullet_collisions() {
    for (InvaderBullet *&invader_bullet: invader_bullets) {
        if (invader_bullet == nullptr) {
            continue;
        }
        int bullet_x = invader_bullet->get_x();
        int bullet_y = invader_bullet->get_y();
        int player_x = player.get_x();
        int player_y = player.get_y();
        if (player_x <= bullet_x && bullet_x <= player_x + constants::PLAYER_WIDTH
            && bullet_y + constants::BULLET_HEIGHT >= player_y) {
            player.set_lives_left(player.get_lives_left() - 1);
            if (player.get_lives_left() > 0) {
                Game::life_lost_reset();
            } else {
                Game::hard_reset();
            }
        }
    }
}

void Game::check_all_bullet_collisions() {}

int Game::get_score() {
    return score;
}

void Game::cleanup() {
    for (InvaderBullet *&invader_bullet: invader_bullets) {
        if (invader_bullet != nullptr) {
            delete invader_bullet;
            invader_bullet = nullptr;
        }
    }
    invader_bullets.clear(); // Clear the current vector after deallocation
    invader_bullets.resize(constants::NUM_INVADER_LEVELS * constants::NUM_INVADERS, nullptr); // Reinitialize

    if (player_bullet != nullptr) {
        delete player_bullet;
        player_bullet = nullptr;
    }
}

void Game::hard_cleanup() {
    cleanup();
    num_invaders_alive = constants::NUM_INVADER_LEVELS * constants::NUM_INVADERS;
    invaders.clear();
}


void Game::life_lost_reset() {
    cleanup();
    player.reset();
}


void Game::hard_reset() {
    hard_cleanup();
    set_game_over();
    player.hard_reset();
    set_all_invaders();
    score = 0;
    level = 0;
}

void Game::check_power_ups() {
    int player_x = player.get_x();
    for (PowerUp &power: power_ups) {
        int power_up_x = power.get_x();
        if (power_up_x <= player_x && player_x <= power_up_x + constants::POWER_UP_WIDTH) {
            PowerUpType type = power.get_power_up_type();
            switch (type) {
                case PowerUpType::SCATTER_BULLET:
                    set_scatter_bullet();
                    break;
                case PowerUpType::BOMB:
                    break;
            }
        }
    }
}

void Game::handle_scatter_bullets(double x, double y) {
    for (int angle = 30; angle <= 150; angle += 30) {
        ScatterBullet *bullet = new ScatterBullet(x + constants::PLAYER_WIDTH / 2, y, angle);
        scatter_bullets.push_back(bullet);
    }
}

void Game::scatter_bullet_detect_invader_collision(ScatterBullet *&bullet) {
    if (bullet == nullptr) {
        return;
    }
    double bullet_x = bullet->get_x();
    double bullet_y = bullet->get_y();
    for (int i = 0; i < invaders.size(); i++) {
        Invader &invader = invaders[i];
        double invader_x = 1.0 * invader.get_x();
        double invader_y = 1.0 * invader.get_y();
        if (invader.is_alive() && invader_x <= bullet_x && bullet_x <= invader_x + constants::INVADER_LENGTH
            && invader_y <= bullet_y && bullet_y <= invader_y + constants::INVADER_HEIGHT) {
            handle_player_bullet_collision(i);
            handle_score_update(invader.get_level());
            delete bullet;
            bullet = nullptr;
        }
    }
}

void Game::scatter_bullet_bound_check(ScatterBullet *&bullet) {
    if (bullet == nullptr) return;
    double bullet_x = bullet->get_x();
    double bullet_y = bullet->get_y();
    double bullet_angle = bullet->get_angle();
    if (bullet_x <= 0) {
        bullet->set_angle(180 - bullet_angle);
    } else if (bullet_x >= constants::WINDOW_WIDTH) {
        bullet->set_angle(180 - bullet_angle);
    }
    if (bullet_y <= 0) {
        bullet->set_angle(360 - bullet_angle);
    } else if (bullet_y >= constants::WINDOW_HEIGHT) {
        bullet->set_angle(360 - bullet_angle);
    }
}

void Game::deactivate_scatter_bullets(ScatterBullet *&bullet) {
    if (bullet == nullptr) return;
    double elapsed_time = bullet->get_elapsed_time();
    if (elapsed_time >= 5) {
        delete bullet;
        bullet = nullptr;
    }
}

