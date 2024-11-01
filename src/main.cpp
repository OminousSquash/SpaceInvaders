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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        Movement::player_movement(p);
//        Movement::invader_movement(invaders);
        Movement::player_bullet_movement(g);
        v.update_screen();
    }
}
