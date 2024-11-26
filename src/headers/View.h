//
// Created by Varun Srinivasan on 31/10/2024.
//

#ifndef CMAKESFMLPROJECT_VIEW_H
#define CMAKESFMLPROJECT_VIEW_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <utility>

class View {
private:
    sf::RenderWindow &window;
    Game &game;
    bool process_input;
public:
    View(Game &game, sf::RenderWindow &window) : game(game), window(window), process_input(true) {}

    void update_screen();

    void draw_base();

    void draw_player();

    void draw_invaders();

    void draw_player_bullet();

    void draw_invader_bullets();

    void display_lives();

    void display_score();

    void display_level();

    void draw_shields();

    void display_game_over();

    void disactivate() {
        process_input = false;
    }

    bool get_process_input() {
        return process_input;
    }

    void reactivate() {
        process_input = true;
    }

    void draw_scatter_bullets();

    void draw_power_ups();

    void draw_scatter_bullets_power_up(PowerUp *&p);

    void draw_bomb_power_up(PowerUp *&p);
};


#endif //CMAKESFMLPROJECT_VIEW_H
