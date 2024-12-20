#include <SFML/Graphics.hpp>
#include <iostream>

#include "headers/constants.h"
#include "headers/Game.h"
#include "headers/View.h"
#include "headers/ActionHandler.h"

using namespace std;

Game initialiseGame() {
    Game g;
    Player p;
    g.set_player(p);
    g.set_all_invaders();
    g.set_all_sheilds();
    return g;
}


int main() {
    auto window = sf::RenderWindow({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT}, "Space Invaders");
    window.setFramerateLimit(144);

    Game g = initialiseGame();
    View v(g, window);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (!g.has_game_started()) {
            Actions::start_game(g);
            Actions::view_rules(g);
        } else if (v.get_process_input()) {
            g.generate_invader_bullets();
            g.generate_power_ups();
            Actions::player_movement(g);
            Actions::player_bullet_movement(g);
            Actions::invader_bullet_movement(g);
            Actions::invader_movement(g.get_invaders());
            Actions::power_up_balls_movement(g);
            Actions::scatter_bullet_movement(g);
            Actions::player_rpg_movement(g);
        } else {
            Actions::restart_game(g);
            v.reactivate();
        }
        v.update_screen();
    }
}
