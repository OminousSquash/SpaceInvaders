//
// Created by Varun Srinivasan on 31/10/2024.
//

#include "headers/View.h"
#include "headers/InvaderBullet.h"
#include "headers/PlayerBullet.h"
#include "headers/constants.h"
#include <SFML/Graphics.hpp>

static inline sf::Sprite makeSprite(const sf::Texture& tex, float w, float h,
                                    float x, float y) {
    sf::Sprite s(tex);
    s.setOrigin(tex.getSize().x * 0.5f, tex.getSize().y * 0.5f);
    s.setScale(w / tex.getSize().x, h / tex.getSize().y);
    s.setPosition(x + w * 0.5f, y + h * 0.5f);
    return s;
}

static inline void drawWithGlow(sf::RenderWindow& win, const sf::Sprite& s,
                                sf::Color glow = sf::Color(0,255,180,90),
                                float scale = 1.18f, int passes = 2) {
    for (int i=0;i<passes;i++) {
        sf::Sprite g = s;
        g.setColor(glow);
        g.setScale(s.getScale().x * (scale + i*0.03f),
                   s.getScale().y * (scale + i*0.03f));
        win.draw(g, sf::BlendAdd);
    }
    win.draw(s);
}

void View::load_textures() {
  if (all_textures_loaded)
    return;
  invader_texture.loadFromFile(constants::INVADER_PATH);
  explosion_texture.loadFromFile(constants::EXPLOSION_IMAGE_PATH);
  player_texture.loadFromFile(constants::PLAYER_IMAGE_PATH);
  hitmarker_texture.loadFromFile(constants::HITMARKER_IMAGE_PATH);
  rpg_texture.loadFromFile(constants::RPG_IMAGE_PATH);
  powerup_texture.loadFromFile(constants::POWER_UP_PATH);
  all_textures_loaded = true;
}

void View::draw_base() {
  sf::RectangleShape base;
  base.setSize(sf::Vector2f(constants::BASE_WIDTH, constants::BASE_HEIGHT));
  base.setPosition(0, constants::WINDOW_HEIGHT - constants::BASE_HEIGHT);
  base.setFillColor(sf::Color::Green);
  window.draw(base);
}

void View::draw_player() {
  Player &p = game.get_player();
  sf::Sprite player_sprite = makeSprite(
      player_texture,
      (float)constants::PLAYER_WIDTH,
      (float)constants::PLAYER_HEIGHT,
      (float)p.get_x(),
      (float)p.get_y());

  // subtle color so it matches background
  player_sprite.setColor(sf::Color(190, 255, 190));

  drawWithGlow(window, player_sprite, sf::Color(60,255,120,90));
}

void View::draw_invaders() {
  auto& invaders = game.get_invaders();
  const float t = frameClock.getElapsedTime().asSeconds();

  for (size_t i = 0; i < invaders.size(); ++i) {
    Invader& inv = invaders[i];
    if (!inv.is_alive()) {
      if (inv.should_explode()) inv.start_explosion();
      if (!inv.explosion_done()) {
        sf::Sprite boom = makeSprite(explosion_texture,
                                     (float)constants::INVADER_LENGTH,
                                     (float)constants::INVADER_HEIGHT,
                                     (float)inv.get_x(), (float)inv.get_y());
        window.draw(boom, sf::BlendAdd);
        inv.decrease_explosion_timer();
      }
      continue;
    }

    sf::Sprite s = makeSprite(invader_texture,
                              (float)constants::INVADER_LENGTH,
                              (float)constants::INVADER_HEIGHT,
                              (float)inv.get_x(), (float)inv.get_y());

    s.move(0.f, std::sin((t*3.f) + (inv.get_x()*0.05f)) * 2.f);

    sf::Uint8 g = 220 - (inv.get_y() / 12 % 3) * 20;
    s.setColor(sf::Color(100, g, 100));

    drawWithGlow(window, s, sf::Color(0,255,160,80));
  }
}


void View::draw_invader_bullets() {
  vector<InvaderBullet *> invader_bullets = game.get_invader_bullets();
  for (int i = 0; i < invader_bullets.size(); i++) {
    InvaderBullet *invader_bullet = invader_bullets[i];
    if (invader_bullet == nullptr) {
      continue;
    }
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(invader_bullet->get_x(),
                                                 invader_bullet->get_y()),
                                    sf::Color::White),
                         sf::Vertex(sf::Vector2f(invader_bullet->get_x(),
                                                 invader_bullet->get_y() +
                                                     constants::BULLET_HEIGHT),
                                    sf::Color::Yellow)};
    window.draw(line, 2, sf::Lines);
  }
}

void View::draw_player_bullet() {
    PlayerBullet *player_bullet = game.get_player_bullet();
    if (player_bullet == nullptr) {
        return;
    }

    float bulletWidth  = 3.2f;
    float bulletHeight = (float)constants::BULLET_HEIGHT;

    sf::RectangleShape bullet(sf::Vector2f(bulletWidth, bulletHeight));
    bullet.setFillColor(sf::Color(230, 255, 255)); // light cyan/white
    bullet.setOrigin(bulletWidth / 2.f, bulletHeight); // origin at bottom center

    bullet.setPosition(
        static_cast<float>(player_bullet->get_x()),
        static_cast<float>(player_bullet->get_y())
    );

    window.draw(bullet);
}

void View::display_lives() {
  sf::Font roboto_font;
  roboto_font.loadFromFile(constants::ROBOTO_FONT_PATH);
  sf::Text lives_left_text;
  lives_left_text.setFont(roboto_font);
  lives_left_text.setString("LIVES LEFT: " +
                            to_string(game.get_player().get_lives_left()));
  lives_left_text.setPosition(0, 0);
  lives_left_text.setFillColor(sf::Color::White);
  window.draw(lives_left_text);
}

void View::display_score() {
  sf::Font roboto_font;
  roboto_font.loadFromFile(constants::ROBOTO_FONT_PATH);
  sf::Text score_string;
  score_string.setFont(roboto_font);
  score_string.setPosition(0, constants::BUFFER);
  score_string.setFillColor(sf::Color::White);
  score_string.setString("SCORE: " + to_string(game.get_score()));
  window.draw(score_string);
}

void View::display_level() {
  sf::Font roboto_font;
  roboto_font.loadFromFile(constants::ROBOTO_FONT_PATH);
  sf::Text level_text;
  level_text.setFont(roboto_font);
  level_text.setString("LEVEL: " + to_string(game.get_level()));
  level_text.setPosition(0, 2 * constants::BUFFER);
  level_text.setFillColor(sf::Color::White);
  window.draw(level_text);
}

void View::display_game_over() {
  sf::Font roboto_font;
  roboto_font.loadFromFile(constants::ROBOTO_FONT_PATH);
  sf::Text game_over;
  game_over.setFont(roboto_font);
  game_over.setCharacterSize(70);
  game_over.setString("GAME OVER\n");
  game_over.setPosition(constants::WINDOW_WIDTH / 3 - 30,
                        constants::WINDOW_HEIGHT / 2 - 50);
  game_over.setFillColor(sf::Color::White);

  sf::Text restart_level;
  restart_level.setFont(roboto_font);
  restart_level.setCharacterSize(70);
  restart_level.setString("PRESS R TO RESTART\n");
  restart_level.setPosition(constants::WINDOW_WIDTH / 4 - 80,
                            constants::WINDOW_HEIGHT / 2 + 40);
  restart_level.setFillColor(sf::Color::White);
  window.draw(game_over);
  window.draw(restart_level);
}

void View::draw_shields() {
  vector<Shield> &shields = game.get_shields();
  for (Shield &shield : shields) {
    vector<ShieldComponent> &shield_components = shield.get_shield_components();
    for (ShieldComponent &component : shield_components) {
      if (!component.is_collidable()) {
        continue;
      }
      sf::RectangleShape shield_component;
      shield_component.setSize(sf::Vector2f(constants::SHIELD_COMPONENT_WIDTH,
                                            component.get_height()));
      shield_component.setFillColor(sf::Color::Green);
      shield_component.setPosition(component.get_x(),
                                   component.get_y() - component.get_height());
      window.draw(shield_component);
    }
  }
}

void View::draw_scatter_bullets() {
    vector<ScatterBullet *> &scatter_bullets = game.get_scatter_bullets();

    for (ScatterBullet *&bullet : scatter_bullets) {
        if (bullet == nullptr) continue;

        float start_x = (float)bullet->get_x();
        float start_y = (float)bullet->get_y();

        float x_length = constants::SCATTER_BULLET_HEIGHT *
                         bullet->get_x_vel() / constants::BULLET_VELOCITY;
        float y_length = constants::SCATTER_BULLET_HEIGHT *
                         bullet->get_y_vel() / constants::BULLET_VELOCITY;
        float end_x = start_x + x_length;
        float end_y = start_y - y_length;

        sf::Vector2f dir(end_x - start_x, end_y - start_y);
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len == 0) continue;

        dir /= len;

        sf::Vector2f perp(-dir.y, dir.x);

        float halfWidth = 1.6f;
        perp *= halfWidth;

        sf::VertexArray quad(sf::TrianglesStrip, 4);

        sf::Color baseColor(0, 200, 255);   // cyan
        sf::Color tipColor(0, 255, 180);    // greenish cyan

        quad[0].position = sf::Vector2f(start_x, start_y) + perp;
        quad[1].position = sf::Vector2f(start_x, start_y) - perp;
        quad[2].position = sf::Vector2f(end_x, end_y) + perp;
        quad[3].position = sf::Vector2f(end_x, end_y) - perp;

        quad[0].color = baseColor;
        quad[1].color = baseColor;
        quad[2].color = tipColor;
        quad[3].color = tipColor;

        window.draw(quad);
    }
}

void View::draw_rpg_power_up(PowerUp *&p) {
    sf::Sprite sprite;
    sprite.setTexture(powerup_texture);

    float scale = (constants::POWER_UP_RADIUS * 2.f) / powerup_texture.getSize().x;
    sprite.setScale(scale, scale);

    sprite.setOrigin(powerup_texture.getSize().x / 2.f, powerup_texture.getSize().y / 2.f);

    sprite.setPosition(p->get_x(), p->get_y());

    sprite.setColor(sf::Color(255, 120, 120));

    window.draw(sprite);
}

void View::draw_scatter_bullets_power_up(PowerUp *&p) {
    sf::Sprite sprite;
    sprite.setTexture(powerup_texture);

    float scale = (constants::POWER_UP_RADIUS * 2.f) / powerup_texture.getSize().x;
    sprite.setScale(scale, scale);

    sprite.setOrigin(powerup_texture.getSize().x / 2.f, powerup_texture.getSize().y / 2.f);
    sprite.setPosition(p->get_x(), p->get_y());

    sprite.setColor(sf::Color(120, 180, 255));

    window.draw(sprite);
}

void View::draw_power_ups() {
  vector<PowerUp *> &power_ups = game.get_power_ups();
  for (PowerUp *&p : power_ups) {
    if (p->get_power_up_type() == PowerUpType::SCATTER_BULLET) {
      draw_scatter_bullets_power_up(p);
    } else if (p->get_power_up_type() == PowerUpType::RPG) {
      draw_rpg_power_up(p);
    }
  }
}

void View::draw_rpg() {
  sf::Sprite rpg_sprite;
  rpg_sprite.setTexture(rpg_texture);

  // Scale the sprite to match PLAYER_WIDTH and PLAYER_HEIGHT
  rpg_sprite.setScale(
      static_cast<float>(constants::RPG_WIDTH) / rpg_texture.getSize().x,
      static_cast<float>(constants::BULLET_HEIGHT) / rpg_texture.getSize().y);

  RPG *&rpg = game.get_rpg();
  if (rpg == nullptr) {
    return;
  }
  rpg_sprite.setPosition(static_cast<float>(rpg->get_x()),
                         static_cast<float>(rpg->get_y()));

  window.draw(rpg_sprite);
}

void View::draw_hitmarkers() {
  if (!game.get_hit_power_up()) {
    return;
  }
  game.disable_hit_power_up();
  sf::Sprite hitmarker_sprite;
  hitmarker_sprite.setTexture(hitmarker_texture);
  // Scale the sprite to match PLAYER_WIDTH and PLAYER_HEIGHT
  hitmarker_sprite.setScale(static_cast<float>(constants::HITMARKER_LENGTH) /
                                hitmarker_texture.getSize().x,
                            static_cast<float>(constants::HITMARKER_WIDTH) /
                                hitmarker_texture.getSize().y);

  // Set the position of the sprite
  hitmarker_sprite.setPosition(static_cast<float>(game.get_player().get_x() +
                                                  constants::PLAYER_WIDTH / 2),
                               static_cast<float>(game.get_player().get_y()));

  // Draw the sprite
  window.draw(hitmarker_sprite);
}

void View::start_screen() {
    sf::Font roboto_font;
    roboto_font.loadFromFile(constants::ROBOTO_FONT_PATH);

    sf::Text start_page;
    start_page.setFont(roboto_font);
    start_page.setCharacterSize(70);
    start_page.setFillColor(sf::Color::White);
    start_page.setString("PRESS SPACE TO START");

    sf::FloatRect start_bounds = start_page.getLocalBounds();
    start_page.setOrigin(start_bounds.left + start_bounds.width / 2.f,
                         start_bounds.top + start_bounds.height / 2.f);

    start_page.setPosition(constants::WINDOW_WIDTH / 2.f,
                           constants::WINDOW_HEIGHT / 3.f + 80);
    window.draw(start_page);

    sf::Text rules_text;
    rules_text.setFont(roboto_font);
    rules_text.setCharacterSize(30);
    rules_text.setFillColor(sf::Color(200, 200, 200));
    rules_text.setString("PRESS R FOR RULES");

    sf::FloatRect rules_bounds = rules_text.getLocalBounds();
    rules_text.setOrigin(rules_bounds.left + rules_bounds.width / 2.f,
                         rules_bounds.top + rules_bounds.height / 2.f);

    rules_text.setPosition(constants::WINDOW_WIDTH / 2.f,
                           constants::WINDOW_HEIGHT / 3.f + 150);
    window.draw(rules_text);
}


void View::controls_screen() {
  sf::Font roboto_font;
  roboto_font.loadFromFile(constants::ROBOTO_FONT_PATH);
  sf::Text controls_page;
  controls_page.setFont(roboto_font);
  controls_page.setCharacterSize(50);
  controls_page.setFillColor(sf::Color::White);

  std::string text = "USE A & D TO MOVE\n";
  text += "USE SPACEBAR TO SHOOT\n";
  text += "BLUE CIRCLE IS SCATTER SHOT\nRED CIRCLE IS RPG\n";
  text += "USE G TO SHOOT RPG\n";
  controls_page.setPosition(100, 210);
  controls_page.setString(text);
  window.draw(controls_page);
  std::string back_text = "USE B TO GO BACK TO START";
  controls_page.setCharacterSize(20);
  controls_page.setPosition(100, 510);
  controls_page.setString(back_text);
  window.draw(controls_page);
}

void View::update_screen() {
    float dt = frameClock.restart().asSeconds();

    window.clear();

    background.update(dt);
    background.draw(window);

    if (game.is_game_over()) {
        View::disactivate();
    } else if (!game.has_game_started() && !game.is_on_game_rules()) {
        start_screen();
    } else if (!game.has_game_started() && game.is_on_game_rules()) {
        controls_screen();
    }

    if (!View::get_process_input()) {
        display_game_over();
    } else if (game.has_game_started()) {
        load_textures();
        draw_base();
        draw_player();
        draw_invaders();
        draw_player_bullet();
        draw_invader_bullets();
        draw_shields();
        display_lives();
        display_score();
        display_level();
        draw_power_ups();
        draw_scatter_bullets();
        draw_rpg();
        draw_hitmarkers();
    }

    window.display();
}
