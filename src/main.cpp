#include <SFML/Graphics.hpp>
#include <iostream>

#include "headers/constants.h"
#include "headers/Game.h"
#include "headers/View.h"
#include "headers/MovementHandler.h"

using namespace std;

Game initialiseGame() {
    Game g;
    Player p;
    g.set_player(p);
    g.set_all_invaders();
    return g;
}


int main() {
    auto window = sf::RenderWindow({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT}, "Space Invaders");
    window.setFramerateLimit(144);

    Game g = initialiseGame();
    View v(g, window);

    while (window.isOpen()) {
        sf::Event event{};
        Player &p = g.get_player();
        vector<Invader> invaders = g.get_invaders();
        vector<InvaderBullet *> invader_bullets = g.get_invader_bullets();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        g.generate_invader_bullets();
        Movement::player_movement(p);
        Movement::player_bullet_movement(g);
        Movement::invader_bullet_movement(g);
        Movement::invader_movement(g.get_invaders());
        v.update_screen();
    }
}
