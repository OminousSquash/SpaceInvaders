#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(10, 20));
    window.setSize(sf::Vector2u(300, 500));
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
