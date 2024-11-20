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
public:
    View(Game &game, sf::RenderWindow &window) : game(game), window(window) {}

    void update_screen();

    void draw_base();

    void draw_player();

    void draw_invaders();

    void draw_player_bullet();

    void draw_invader_bullets();

    void display_lives();

    void display_score();

    void display_level();
};


#endif //CMAKESFMLPROJECT_VIEW_H
