#include "../include/core/config.h"
#include "../include/core/gameobjects/shape.h"
#include "../include/core/physics/physics.h"
#include "../include/core/random.h"

int main() {
  // ─── Window & Settings ───────────────────────────────────────────
  GameWindow gameWindow;
  sf::ContextSettings settings;
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  gameWindow.WINDOW_WIDTH = desktop.size.x;
  gameWindow.WINDOW_HEIGHT = desktop.size.y;
  settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

  sf::RenderWindow window(
      sf::VideoMode({gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT}),
      gameWindow.WINDOW_TITLE);

  window.setFramerateLimit(gameWindow.FRAME_RATE);

  // ─── Global Setup ────────────────────────────────────────────────
  Random random;
  PhysicsEngine::Verlet verlet;
  PhysicsEngine::Collision collision;
  sf::Clock clock;

  Shape shape;
  shape.Initialize(window);

  for (auto &point : shape.points) {
    point.color = random.setColor();
  }

  // ─── Main Loop ───────────────────────────────────────────────────
  while (window.isOpen()) {

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // ─── Update Logic ─────────────────────────────────────────────
    float dt = clock.restart().asSeconds();

    for (auto &point : shape.points) {
      verlet.ApplyVerlet(point, dt);
      collision.ResolveWindowCollision(point, window);
    }

    for (size_t i = 0; i < shape.points.size(); ++i) {
      for (size_t j = i + 1; j < shape.points.size(); ++j) {
        collision.ResolveCircleCollision(shape.points[i], shape.points[j]);
      }
    }

    // ─── Render ─────────────────────────────────────────────────
    window.clear(sf::Color::Black);
    shape.Draw(window);
    window.display();
  }

  return 0;
}
