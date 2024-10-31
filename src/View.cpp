//
// Created by Varun Srinivasan on 31/10/2024.
//

#include "View.h"
#include <SFML/Graphics.hpp>
#include "constants.h"

void View::draw_base() {
    sf::RectangleShape base;
    base.setSize(sf::Vector2f(constants::BASE_WIDTH, constants::BASE_HEIGHT));
    base.setPosition(0, constants::WINDOW_HEIGHT - constants::BASE_HEIGHT);
    base.setFillColor(sf::Color::Green);
    window.draw(base);
}

void View::draw_player() {
    Player &p = game.get_player();
    int player_x = p.get_x();
    int player_y = p.get_y();
    sf::RectangleShape player;
    player.setSize(sf::Vector2f(40, 40));
    player.setPosition(player_x, player_y);
    player.setFillColor(sf::Color::White);
    window.draw(player);
}


void View::draw_invaders() {

}

void View::update_screen() {
    window.clear(sf::Color::Black);
    draw_base();
    draw_player();
    window.display();
}
