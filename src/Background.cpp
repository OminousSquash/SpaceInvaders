#include "./headers/Background.h"
#include <cstdlib>
#include <cmath>

Background::Background(int width, int height)
    : windowWidth(width), windowHeight(height) {
    for (int i = 0; i < 200; i++) {
        Star s;
        s.pos = sf::Vector2f(rand() % windowWidth,
                             rand() % windowHeight);
        s.speed = 30.f + static_cast<float>(rand() % 70);
        int brightness = 180 + rand() % 75;
        s.color = sf::Color(brightness, brightness, brightness);
        stars.push_back(s);
    }
}

void Background::update(float dt) {
    // move stars down
    for (auto& s : stars) {
        s.pos.y += s.speed * dt;
        if (s.pos.y > windowHeight) {
            s.pos.y = 0;
            s.pos.x = rand() % windowWidth;
        }
    }

    // maybe spawn a shooting star
    if (shootingStarClock.getElapsedTime().asSeconds() > 5.f) {
        if (rand() % 100 < 10) { // 10% chance every 5 seconds
            ShootingStar ss;
            ss.pos = sf::Vector2f(rand() % windowWidth, 0.f);
            ss.vel = sf::Vector2f(-200.f, 300.f);
            ss.life = 1.5f;
            shootingStars.push_back(ss);
        }
        shootingStarClock.restart();
    }

    // update existing shooting stars
    for (auto it = shootingStars.begin(); it != shootingStars.end();) {
        it->pos += it->vel * dt;
        it->life -= dt;
        if (it->life <= 0) {
            it = shootingStars.erase(it);
        } else {
            ++it;
        }
    }
}

void Background::draw(sf::RenderWindow& window) {
    drawGradient(window);
    drawStars(window);
    drawShootingStars(window, 0.f);
}

void Background::drawGradient(sf::RenderWindow& window) {
    sf::VertexArray quad(sf::Quads, 4);

    quad[0].position = {0.f, 0.f};
    quad[1].position = {(float)windowWidth, 0.f};
    quad[2].position = {(float)windowWidth, (float)windowHeight};
    quad[3].position = {0.f, (float)windowHeight};

    quad[0].color = sf::Color(10, 10, 40);
    quad[1].color = sf::Color(10, 10, 40);
    quad[2].color = sf::Color::Black;
    quad[3].color = sf::Color::Black;

    window.draw(quad);
}

void Background::drawStars(sf::RenderWindow& window) {
    sf::VertexArray va(sf::Points, stars.size());
    for (size_t i = 0; i < stars.size(); i++) {
        va[i].position = stars[i].pos;
        va[i].color = stars[i].color;
    }
    window.draw(va);
}

void Background::drawShootingStars(sf::RenderWindow& window, float dt) {
    for (auto& s : shootingStars) {
        sf::VertexArray streak(sf::Lines, 2);
        streak[0].position = s.pos;
        streak[0].color = sf::Color::White;
        streak[1].position = s.pos - s.vel * 0.1f; // trailing streak
        streak[1].color = sf::Color(255, 255, 255, 120);
        window.draw(streak);
    }
}
