//
// Created by Varun Srinivasan on 30/10/2024.
//

#define _USE_MATH_DEFINES

#include "headers/Game.h"
#include <ctime>
#include <cmath>
#include <random> // For random number generation

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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1e6);
    for (int i = 0; i < invaders.size(); i++) {
        Invader &invader = invaders[i];
        int x = dis(gen);
        if (invader.is_alive() && invader_bullets[i] == nullptr && x >= constants::INVADER_BULLET_RNG_THRESHOLD) {
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

void Game::check_player_power_up_collision(PowerUp *&power) {
    int player_x_left = player.get_x();
    int player_x_right = player_x_left + constants::PLAYER_WIDTH;
    int player_y = player.get_y();
    int power_x_left = power->get_x() - constants::POWER_UP_RADIUS;
    int power_x_right = power->get_x() + constants::POWER_UP_RADIUS;
    int power_y_top = power->get_y() - constants::POWER_UP_RADIUS;
    int power_y_bottom = power->get_y() + constants::POWER_UP_RADIUS;
    if (!(power_x_left > player_x_right || player_x_left > power_x_right) &&
        power_y_top <= player_y &&
        player_y <= power_y_bottom) {
        cout << "SCATTER POWER UP" << endl;
        switch (power->get_power_up_type()) {
            case PowerUpType::BOMB:
                break;
            case PowerUpType::SCATTER_BULLET:
                enable_scatter_bullet();
                break;
        }
    }
}

void Game::power_up_bounds_check() {
    for (PowerUp *&p: power_ups) {
        int y = p->get_y();
        if (y >= constants::WINDOW_HEIGHT) {
            delete p;
            p = nullptr;
        }
    }
    vector<PowerUp *> new_power_ups;
    for (PowerUp *&p: power_ups) {
        if (p != nullptr) {
            new_power_ups.push_back(p);
        }
    }
    power_ups = new_power_ups;
}

void Game::handle_scatter_bullets(double x, double y) {
    for (int factor = 1; factor <= 5; factor++) {
        ScatterBullet *bullet = new ScatterBullet(x + constants::PLAYER_WIDTH / 2, y, M_PI * factor / 6);
        scatter_bullets.push_back(bullet);
    }
}

void Game::scatter_bullet_detect_invader_collision(ScatterBullet *&bullet) {
    if (bullet == nullptr) {
        return;
    }
    double bullet_angle = bullet->get_angle();
    double bullet_x = bullet->get_x() + constants::BULLET_HEIGHT * cos(bullet_angle);
    double bullet_y = bullet->get_y() - constants::BULLET_HEIGHT * sin(bullet_angle);
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
    double bullet_x_vel = bullet->get_x_vel();
    double bullet_y_vel = bullet->get_y_vel();
    if (bullet_x <= 0 || bullet_x >= constants::WINDOW_WIDTH) {
        bullet->set_x_vel(-1.0 * bullet_x_vel);
    } else if (bullet_y <= 0 || bullet_y >= constants::WINDOW_HEIGHT - constants::BASE_HEIGHT) {
        bullet->set_y_vel(-1.0 * bullet_y_vel);
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

int get_random_in_range(int min, int max) {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr))); // Seed RNG once
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void Game::generate_power_ups() {
    double scatter_elapsed = get_time_since_last_scatter_power();
    if (scatter_elapsed >= constants::SCATTER_POWER_DELAY) {
//        cout << "POWERUPS CREATED" << endl;
        int random_x = get_random_in_range(constants::POWER_UP_RADIUS,
                                           constants::WINDOW_WIDTH - constants::POWER_UP_RADIUS);
        power_ups.push_back(new PowerUp(random_x, 0, PowerUpType::SCATTER_BULLET));
        time_of_scatter_power = std::chrono::steady_clock::now();
    }
//    if (fmod(elapsed, 20.0) == 0 && elapsed > 0) {
//        power_ups.push_back(new PowerUp(0, constants::WINDOW_WIDTH / 2, PowerUpType::BOMB));
//    }
}

