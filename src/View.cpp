//
// Created by Varun Srinivasan on 31/10/2024.
//

#include "View.h"
#include <SFML/Graphics.hpp>
#include "constants.h"

void View::update_screen() {
    window.clear(sf::Color::Black);
    sf::RectangleShape base;
    base.setSize(sf::Vector2f(constants::BASE_WIDTH, constants::BASE_HEIGHT));
    base.setPosition(0, constants::WINDOW_HEIGHT - constants::BASE_HEIGHT);
    window.draw(base);
    window.display();
}
