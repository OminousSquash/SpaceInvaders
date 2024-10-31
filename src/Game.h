//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H


#include "player.h"
#include "playercontroller.h"
#include "shield.h"
#include "Invader.h"

#include <iostream>
#include <vector>

using namespace std;

class Game {
private:
    int level;
    Player player;
    PlayerController player_controller;
    vector<Shield> shields;
    vector<Invader> invaders;
    static Game *instance;

private:

    Game() : level(0) {}

public:
    static Game *getInstance() {
        if (instance == nullptr) {
            instance = new Game();
        }
        return instance;
    }

    void update_level();

    void set_player(Player &p);

    void set_player_controller(PlayerController &pc);

    void add_sheild(Shield &sheild);

    void add_invader(Invader &invader);

    void set_all_invaders();

    void set_all_sheilds();
};


#endif //CMAKESFMLPROJECT_GAME_H
