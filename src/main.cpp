#include <SFML/Graphics.hpp>
#include <iostream>

#include "headers/constants.h"
#include "headers/Game.h"
#include "headers/View.h"

using namespace std;

Game initialiseGame() {
    Game g;
    Player p;
    PlayerController pc;
    g.set_player(p);
    g.set_player_controller(pc);
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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        v.update_screen();
    }
}
