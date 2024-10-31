//
// Created by Varun Srinivasan on 30/10/2024.
//

#include "Game.h"

void Game::update_level() {

}

void Game::set_player(Player &p) {
    this->player = player;
}

void Game::set_all_invaders() {

}

void Game::set_all_sheilds() {

}

void Game::add_invader(Invader &invader) {
    invaders.push_back(invader);
}

void Game::add_sheild(Shield &sheild) {
    shields.push_back(sheild);
}

