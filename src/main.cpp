#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.h"
#include "Game.h"

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

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        sf::RectangleShape r;
        r.setSize(sf::Vector2f(constants::BASE_WIDTH, constants::BASE_HEIGHT));
        r.setFillColor(sf::Color::Green);
        r.setPosition(0, constants::WINDOW_HEIGHT - constants::BASE_HEIGHT);
        window.draw(r);
        window.display();
    }
}
