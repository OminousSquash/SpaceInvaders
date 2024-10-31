//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H


#include "Player.h"
#include "PlayerController.h"
#include "Shield.h"
#include "Invader.h"

#include <iostream>
#include <vector>

using namespace std;

class Game {
private:
    int level;
    int score;
    Player player;
    PlayerController player_controller;
    vector<Shield> shields;
    vector<Invader> invaders;
    static Game *instance;

public:
    Game() : level(0), score(0) {}

    void update_level();

    void set_player(Player p);

    void set_player_controller(PlayerController pc);

    void add_sheild(Shield &sheild);

    void add_invader(Invader &invader);

    void set_all_invaders();

    void set_all_sheilds();
};


#endif //CMAKESFMLPROJECT_GAME_H
