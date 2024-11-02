//
// Created by Varun Srinivasan on 30/10/2024.
//

#include "headers/Game.h"

void Game::update_level() {

}

void Game::set_player(Player p) {
    this->player = p;
}

void Game::set_all_invaders() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            Invader inv(j, i);
            add_invader(inv);
        }
    }
}

void Game::set_all_sheilds() {

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
}

void Game::check_player_bullet_collisions() {
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
            return;
        }
    }
}