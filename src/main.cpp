#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.h"

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    std::cout << "Key Code:" << event.key.code << std::endl;
                    std::cout << "Key Scancode:" << event.key.scancode << std::endl;
                    if (event.key.code == sf::Keyboard::D) {
                        std::cout << "PRESSED D" << std::endl;
                    }
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::Black);
        window.display();
    }
}
