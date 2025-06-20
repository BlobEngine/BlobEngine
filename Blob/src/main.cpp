#include "../include/core/config.h"
#include "../include/core/gameobjects/shape.h"
#include <random>

sf::Vector2f Random(sf::RenderWindow& window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, window.getSize().x - 100.f);
    std::uniform_real_distribution<float> distY(0.f, window.getSize().y - 100.f);

    return sf::Vector2f{ distX(gen), distY(gen) };
}

int main() {
  GameWindow gameWindow;
  sf::ContextSettings settings;
  settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

  sf::RenderWindow window(
      sf::VideoMode({gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT}),
      gameWindow.WINDOW_TITLE);
  window.setFramerateLimit(gameWindow.FRAME_RATE);

  Shape tri;
  tri.gravity = sf::Vector2f{0.0f, 100.0f};
  int pointQuantity = 50;

  for (int i = 0; i < pointQuantity; ++i) {
    Points p;
    p.position = sf::Vector2f(Random(window));
    p.velocity = sf::Vector2f(100.0f, 100.0f);
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
    tri.Move(dt);

    window.clear(sf::Color::Black);

    for (auto& p : tri.points) 
    {
      sf::CircleShape shape(p.radius);
      shape.setOrigin(sf::Vector2f{p.radius, p.radius});
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(p.position);
      window.draw(shape);

      tri.WindowCollision(window, p);

    }  

    for (auto& pa : tri.points)
    {
        for (auto& pb : tri.points)
        {
            if (&pa != &pb)
            {
                tri.CircleCollision(pa, pb);
            }
        }

    }

    window.display();
  }

  return 0;
}
