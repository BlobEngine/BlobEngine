#include "../include/core/config.h"
#include "../include/core/gameobjects/shape.h"

int main() {
  GameWindow gameWindow;
  sf::ContextSettings settings;
  settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

  sf::RenderWindow window(
      sf::VideoMode({gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT}),
      gameWindow.WINDOW_TITLE);
  window.setFramerateLimit(gameWindow.FRAME_RATE);

  Shape tri;
  tri.gravity = sf::Vector2f{0.0f, 20.0f};
  int pointQuantity = 300;

  for (int i = 0; i < pointQuantity; ++i) {
    Points p;
    p.position = sf::Vector2f(100 + i * 40, 100);
    p.velocity = sf::Vector2f(80.0f, 80.0f);
    tri.points.push_back(p);
  }

  sf::Clock clock;

  // Main loop
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }
    float dt = clock.restart().asSeconds();
    tri.Update(dt);

    window.clear(sf::Color::Black);

    for (auto& p : tri.points) {
      sf::CircleShape shape(p.radius);
      shape.setOrigin(sf::Vector2f{p.radius, p.radius});
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(p.position);
      window.draw(shape);

      tri.WindowCollision(window, p);
    }

  

    window.display();
  }

  return 0;
}
