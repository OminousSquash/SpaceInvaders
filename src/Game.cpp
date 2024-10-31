//
// Created by Varun Srinivasan on 30/10/2024.
//

#include "headers/Game.h"

void Game::update_level() {

}

void Game::set_player(Player p) {
    this->player = p;
}

void Game::set_player_controller(PlayerController pc) {
    this->player_controller = pc;
}

void Game::set_all_invaders() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            Invader inv(j, i);
            std::cout << "level: " << inv.get_level() << " position: " << inv.get_position() << std::endl;
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

