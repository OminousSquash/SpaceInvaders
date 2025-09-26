#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Star {
    sf::Vector2f pos;
    float speed;
    sf::Color color;
};

struct ShootingStar {
    sf::Vector2f pos, vel;
    float life;
};

class Background {
public:
    Background(int width, int height);

    void update(float dt);

    void draw(sf::RenderWindow& window);

private:
    int windowWidth;
    int windowHeight;

    std::vector<Star> stars;
    std::vector<ShootingStar> shootingStars;

    sf::Clock shootingStarClock;

    void drawGradient(sf::RenderWindow& window);
    void drawStars(sf::RenderWindow& window);
    void drawShootingStars(sf::RenderWindow& window, float dt);
};
