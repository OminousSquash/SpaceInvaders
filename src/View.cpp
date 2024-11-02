//
// Created by Varun Srinivasan on 31/10/2024.
//

#include "headers/View.h"
#include <SFML/Graphics.hpp>
#include "headers/constants.h"
#include "headers/InvaderBullet.h"
#include "headers/PlayerBullet.h"

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
    vector<Invader> invaders = game.get_invaders();
    for (int i = 0; i < invaders.size(); i++) {
        Invader &invader = invaders[i];
        if (!invader.is_alive()) {
            continue;
        }
        sf::RectangleShape inv_rect;
        inv_rect.setPosition(invader.get_x(), invader.get_y());
        inv_rect.setSize(sf::Vector2f(constants::INVADER_LENGTH, constants::INVADER_HEIGHT));
        inv_rect.setFillColor(sf::Color::Red);
        window.draw(inv_rect);
    }
}

void View::draw_invader_bullets() {

}

void View::draw_player_bullet() {
    PlayerBullet *player_bullet = game.get_player_bullet();
    if (player_bullet == nullptr) {
        return;
    }
    sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(player_bullet->get_x(), player_bullet->get_y()), sf::Color::White),
                    sf::Vertex(sf::Vector2f(player_bullet->get_x(), player_bullet->get_y() - constants::BULLET_HEIGHT),
                               sf::Color::White)
            };
    window.draw(line, 2, sf::Lines);
}

void View::update_screen() {
    window.clear(sf::Color::Black);
    draw_base();
    draw_player();
    draw_invaders();
    draw_player_bullet();
    window.display();
}
