#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.h"
#include "Game.h"
#include "View.h"

using namespace std;

Game initialiseGame() {
    Game g;
    Player p;
    PlayerController pc;
    g.set_player(p);
    g.set_player_controller(pc);
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
