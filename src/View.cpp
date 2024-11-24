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
    vector<Invader> &invaders = game.get_invaders();
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
    vector<InvaderBullet *> invader_bullets = game.get_invader_bullets();
    for (int i = 0; i < invader_bullets.size(); i++) {
        InvaderBullet *invader_bullet = invader_bullets[i];
        if (invader_bullet == nullptr) {
            continue;
        }
        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(invader_bullet->get_x(), invader_bullet->get_y()), sf::Color::White),
                        sf::Vertex(sf::Vector2f(invader_bullet->get_x(),
                                                invader_bullet->get_y() + constants::BULLET_HEIGHT),
                                   sf::Color::Yellow)
                };
        window.draw(line, 2, sf::Lines);
    }
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

void View::display_lives() {
    sf::Font roboto_font;
    roboto_font.loadFromFile(
            "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/SFMLFonts/roboto/Roboto-Bold.ttf");
    sf::Text lives_left_text;

    lives_left_text.setFont(roboto_font);
    lives_left_text.setString("LIVES LEFT: " + to_string(game.get_player().get_lives_left()));
    lives_left_text.setPosition(0, 0);
    lives_left_text.setFillColor(sf::Color::White);
    window.draw(lives_left_text);
}

void View::display_score() {
    sf::Font roboto_font;
    roboto_font.loadFromFile(
            "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/SFMLFonts/roboto/Roboto-Bold.ttf");
    sf::Text score_string;
    score_string.setFont(roboto_font);
    score_string.setPosition(0, constants::BUFFER);
    score_string.setFillColor(sf::Color::White);
    score_string.setString("SCORE: " + to_string(game.get_score()));
    window.draw(score_string);
}

void View::display_level() {
    sf::Font roboto_font;
    roboto_font.loadFromFile(
            "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/SFMLFonts/roboto/Roboto-Bold.ttf");
    sf::Text level_text;
    level_text.setFont(roboto_font);
    level_text.setString("LEVEL: " + to_string(game.get_level()));
    level_text.setPosition(0, 2 * constants::BUFFER);
    level_text.setFillColor(sf::Color::White);
    window.draw(level_text);
}

void View::display_game_over() {
    sf::Font roboto_font;
    roboto_font.loadFromFile(
            "/Users/varunsrinivasan/Documents/Projects/gameDev/SpaceInvaders/SFMLFonts/roboto/Roboto-Bold.ttf");
    sf::Text game_over;
    game_over.setFont(roboto_font);
    game_over.setCharacterSize(70);
    game_over.setString("GAME OVER\n");
    game_over.setPosition(constants::WINDOW_WIDTH / 3 - 30, constants::WINDOW_HEIGHT / 2 - 50);
    game_over.setFillColor(sf::Color::White);

    sf::Text restart_level;
    restart_level.setFont(roboto_font);
    restart_level.setCharacterSize(70);
    restart_level.setString("PRESS R TO RESTART\n");
    restart_level.setPosition(constants::WINDOW_WIDTH / 4 - 80, constants::WINDOW_HEIGHT / 2 + 40);
    restart_level.setFillColor(sf::Color::White);
    window.draw(game_over);
    window.draw(restart_level);
}

void View::draw_shields() {
    vector<Shield> &shields = game.get_shields();
    for (Shield &shield: shields) {
        vector<ShieldComponent> &shield_components = shield.get_shield_components();
        for (ShieldComponent &component: shield_components) {
            if (!component.is_collidable()) {
                continue;
            }
            sf::RectangleShape shield_component;
            shield_component.setSize(sf::Vector2f(constants::SHIELD_COMPONENT_WIDTH, component.get_height()));
            shield_component.setFillColor(sf::Color::Green);
            shield_component.setPosition(component.get_x(), component.get_y() - component.get_height());
            window.draw(shield_component);
        }
    }
}

void View::update_screen() {
    window.clear(sf::Color::Black);
    if (game.is_game_over()) {
        View::disactivate();
    }
    if (!View::get_process_input()) {
        display_game_over();
    } else {
        draw_base();
        draw_player();
        draw_invaders();
        draw_player_bullet();
        draw_invader_bullets();
        draw_shields();
        display_lives();
        display_score();
        display_level();
    }
    window.display();
}
