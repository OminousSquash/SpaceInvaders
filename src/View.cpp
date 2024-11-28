//
// Created by Varun Srinivasan on 31/10/2024.
//

#include "headers/View.h"
#include <SFML/Graphics.hpp>
#include "headers/constants.h"
#include "headers/InvaderBullet.h"
#include "headers/PlayerBullet.h"


void View::load_textures() {
    if (all_textures_loaded) return;
    invader_texture.loadFromFile(constants::INVADER_PATH);
    explosion_texture.loadFromFile(constants::EXPLOSION_IMAGE_PATH);
    player_texture.loadFromFile(constants::PLAYER_IMAGE_PATH);
    hitmarker_texture.loadFromFile(constants::HITMARKER_IMAGE_PATH);
    roboto_font.loadFromFile(constants::ROBOTO_FONT_PATH);
    all_textures_loaded = true;
}

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
    sf::Sprite player_sprite;
    player_sprite.setTexture(player_texture);

    // Scale the sprite to match PLAYER_WIDTH and PLAYER_HEIGHT
    player_sprite.setScale(
            static_cast<float>(constants::PLAYER_WIDTH) / player_texture.getSize().x,
            static_cast<float>(constants::PLAYER_HEIGHT) / player_texture.getSize().y
    );

    // Set the position of the sprite
    player_sprite.setPosition(player_x, player_y);

    // Draw the sprite
    window.draw(player_sprite);
}


void View::draw_invaders() {
    vector<Invader> &invaders = game.get_invaders();
    for (int i = 0; i < invaders.size(); i++) {
        Invader &invader = invaders[i];
        if (!invader.is_alive()) {
            if (invader.should_explode()) {
                invader.start_explosion();
            }
            if (!invader.explosion_done()) {
                sf::Sprite explosion_sprite;
                explosion_sprite.setTexture(explosion_texture);
                explosion_sprite.setScale(
                        static_cast<float>(constants::INVADER_LENGTH) / explosion_texture.getSize().x,
                        static_cast<float>(constants::INVADER_HEIGHT) / explosion_texture.getSize().y
                );
                explosion_sprite.setPosition(static_cast<float>(invader.get_x()), static_cast<float>(invader.get_y()));
                window.draw(explosion_sprite);
                invader.decrease_explosion_timer();
                continue;
            } else continue;
        }
        sf::Sprite invader_sprite;
        invader_sprite.setTexture(invader_texture);
        invader_sprite.setScale(
                static_cast<float>(constants::INVADER_LENGTH) / invader_texture.getSize().x,
                static_cast<float>(constants::INVADER_HEIGHT) / invader_texture.getSize().y
        );

        invader_sprite.setPosition(static_cast<float>(invader.get_x()), static_cast<float>(invader.get_y()));

        window.draw(invader_sprite);
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
    sf::Text lives_left_text;
    lives_left_text.setFont(roboto_font);
    lives_left_text.setString("LIVES LEFT: " + to_string(game.get_player().get_lives_left()));
    lives_left_text.setPosition(0, 0);
    lives_left_text.setFillColor(sf::Color::White);
    window.draw(lives_left_text);
}

void View::display_score() {
    sf::Text score_string;
    score_string.setFont(roboto_font);
    score_string.setPosition(0, constants::BUFFER);
    score_string.setFillColor(sf::Color::White);
    score_string.setString("SCORE: " + to_string(game.get_score()));
    window.draw(score_string);
}

void View::display_level() {
    sf::Text level_text;
    level_text.setFont(roboto_font);
    level_text.setString("LEVEL: " + to_string(game.get_level()));
    level_text.setPosition(0, 2 * constants::BUFFER);
    level_text.setFillColor(sf::Color::White);
    window.draw(level_text);
}

void View::display_game_over() {
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

void View::draw_scatter_bullets() {
    vector<ScatterBullet *> &scatter_bullets = game.get_scatter_bullets();
    for (ScatterBullet *&bullet: scatter_bullets) {
        if (bullet != nullptr) {
            double start_x = bullet->get_x();
            double start_y = bullet->get_y();
            double x_length = 1.0 * constants::SCATTER_BULLET_HEIGHT * bullet->get_x_vel() / constants::BULLET_VELOCITY;
            double y_length = 1.0 * constants::SCATTER_BULLET_HEIGHT * bullet->get_y_vel() / constants::BULLET_VELOCITY;
            double end_x = 1.0 * start_x + x_length;
            double end_y = 1.0 * start_y - y_length;
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(static_cast<float>(start_x), static_cast<float>(start_y)),
                               sf::Color::Green),
                    sf::Vertex(sf::Vector2f(static_cast<float>(end_x), static_cast<float>(end_y)), sf::Color::Blue)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

void View::draw_rpg_power_up(PowerUp *&p) {
    sf::Vector2f center(p->get_x(), p->get_y());
    sf::CircleShape circle(constants::POWER_UP_RADIUS);
    circle.setOrigin(constants::POWER_UP_RADIUS, constants::POWER_UP_RADIUS);
    circle.setPosition(center);
    circle.setFillColor(sf::Color::Red);
    window.draw(circle);
}

void View::draw_scatter_bullets_power_up(PowerUp *&p) {
    sf::Vector2f center(p->get_x(), p->get_y());
    sf::CircleShape circle(constants::POWER_UP_RADIUS);
    circle.setOrigin(constants::POWER_UP_RADIUS, constants::POWER_UP_RADIUS);
    circle.setPosition(center);
    circle.setFillColor(sf::Color::Blue);
    window.draw(circle);
}

void View::draw_power_ups() {
    vector<PowerUp *> &power_ups = game.get_power_ups();
    for (PowerUp *&p: power_ups) {
        if (p->get_power_up_type() == PowerUpType::SCATTER_BULLET) {
            draw_scatter_bullets_power_up(p);
        } else if (p->get_power_up_type() == PowerUpType::RPG) {
            draw_rpg_power_up(p);
        }
    }
}

void View::draw_rpg() {
    RPG *&rpg = game.get_rpg();
    if (rpg == nullptr) return;
    int x = rpg->get_x();
    int y = rpg->get_y();
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
    rect.setSize(sf::Vector2f(constants::RPG_WIDTH, constants::BULLET_HEIGHT));
    rect.setFillColor(sf::Color::Red);
    window.draw(rect);
}

void View::draw_hitmarkers() {
    if (!game.get_hit_power_up()) {
        return;
    }
    game.disable_hit_power_up();
    sf::Sprite hitmarker_sprite;
    hitmarker_sprite.setTexture(hitmarker_texture);
    // Scale the sprite to match PLAYER_WIDTH and PLAYER_HEIGHT
    hitmarker_sprite.setScale(
            static_cast<float>(constants::HITMARKER_LENGTH) / hitmarker_texture.getSize().x,
            static_cast<float>(constants::HITMARKER_WIDTH) / hitmarker_texture.getSize().y
    );

    // Set the position of the sprite
    hitmarker_sprite.setPosition(static_cast<float>(game.get_player().get_x() + constants::PLAYER_WIDTH / 2),
                                 static_cast<float>(game.get_player().get_y()));

    // Draw the sprite
    window.draw(hitmarker_sprite);
}

void View::update_screen() {
    window.clear(sf::Color::Black);
    if (game.is_game_over()) {
        View::disactivate();
    }
    if (!View::get_process_input()) {
        display_game_over();
    } else {
        load_textures();
        draw_base();
        draw_player();
        draw_invaders();
        draw_player_bullet();
        draw_invader_bullets();
        draw_shields();
        display_lives();
        display_score();
        display_level();
        draw_power_ups();
        draw_scatter_bullets();
        draw_rpg();
        draw_hitmarkers();
    }
    window.display();
}
