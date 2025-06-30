#include "../external/Imgui-SFML/include/imgui-SFML.h"
#include "../external/Imgui/include/imgui.h"
#include "../include/core/config.h"
#include "../include/core/gameobjects/shape.h"
#include "../include/core/input.h"
#include "../include/core/physics/physics.h"
#include "../include/core/random.h"
#include "../include/editor/debugmenu.h"
#include "../include/core/gameobjects/spring.h"

int main() 
{
  // ─── Window & Settings ───────────────────────────────────────────
  GameWindow gameWindow;
  sf::ContextSettings settings;
  settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

  // Fullscreen
  // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  // gameWindow.WINDOW_WIDTH = desktop.size.x;
  // gameWindow.WINDOW_HEIGHT = desktop.size.y;

  sf::RenderWindow window(
      sf::VideoMode({gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT}),
      gameWindow.WINDOW_TITLE);
  ImGui::SFML::Init(window);

  window.setFramerateLimit(gameWindow.FRAME_RATE);

  // ─── Global Setup ────────────────────────────────────────────────
  Random random;
  sf::Clock clock;

  Shape shape;
  shape.Initialize(window);

  std::vector<Spring> springs;
  for (size_t i = 0; i < shape.points.size(); ++i) {
      for (size_t j = i + 1; j < shape.points.size(); ++j) {
     
          springs.emplace_back(&shape.points[i], &shape.points[j], 60.0f); // stiffness
      }
  }


  for (auto &point : shape.points) {
    point.color = sf::Color::White;
  }

  // ─── Main Loop ───────────────────────────────────────────────────
  while (window.isOpen()) {

    while (const std::optional event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // ─── Update Logic ─────────────────────────────────────────────
    sf::Time delta = clock.restart();
    ImGui::SFML::Update(window, delta);
    float dt = delta.asSeconds();

    Input::Mouse::Drag(shape.points, window);

    for (auto &point : shape.points) {
      PhysicsEngine::Verlet::Apply(point, dt);
      PhysicsEngine::Collision::ResolveWindow(point, window);
    }

    for (size_t i = 0; i < shape.points.size(); ++i) {
      for (size_t j = i + 1; j < shape.points.size(); ++j) {
          PhysicsEngine::Collision::ResolveCircle(shape.points[i], shape.points[j]);
      }
    }

    for (auto& spring : springs) {
        spring.restLength = 100.0f;
        PhysicsEngine::Spring::ApplyForce(*spring.a, *spring.b, spring.restLength, spring.springConstant, dt);
    }


    // ─── Render ─────────────────────────────────────────────────

    window.clear(sf::Color::Black);
    ImGui::Begin("DebugMenu");
    Editor::drawDebugMenu(shape);
    ImGui::End();
    shape.Draw(window);

    for (auto& line : PhysicsEngine::Spring::springLinesToDraw) {
        sf::Vertex vertices[2] = {
            sf::Vertex{line.first, sf::Color::White},
            sf::Vertex{line.second, sf::Color::White}
        };

        window.draw(vertices, 2, sf::PrimitiveType::Lines);
    }

    PhysicsEngine::Spring::springLinesToDraw.clear();
    ImGui::SFML::Render(window);
    window.display();
  }

  return 0;
}
