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
    bool all_textures_loaded;
    sf::Texture invader_texture;
    sf::Texture player_texture;
    sf::Texture explosion_texture;
    sf::Texture hitmarker_texture;
    sf::Texture rpg_texture;
    sf::Font roboto_font;

public:

    View(Game &game, sf::RenderWindow &window) :
            game(game),
            window(window),
            process_input(true),
            all_textures_loaded(false) {}

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

    void draw_rpg_power_up(PowerUp *&p);

    void draw_rpg();

    void draw_hitmarkers();

    void load_textures();
};


#endif //CMAKESFMLPROJECT_VIEW_H
