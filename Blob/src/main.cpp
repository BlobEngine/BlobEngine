#include "../external/Imgui-SFML/include/imgui-SFML.h"
#include "../external/Imgui/include/imgui.h"

#include "../include/core/entities/shape.h"
#include "../include/core/entities/spring.h"
#include "../include/core/input/mouse.h"
#include "../include/core/system/config.h"
#include "../include/core/system/random.h"
#include "../include/editor/debugmenu.h"
#include "../include/editor/grid.h"
#include <iostream>

int main() {
  GameWindow gameWindow;
  sf::ContextSettings settings;
  settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

  // Create main application window
  sf::RenderWindow window(
      sf::VideoMode({gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT}),
      gameWindow.WINDOW_TITLE, sf::Style::Default);
  window.setFramerateLimit(gameWindow.FRAME_RATE);

  ImGui::SFML::Init(window); // Initialize ImGui for SFML

  // Core systems
  Random random;
  sf::Clock clock;
  Grid grid;

  // Simulation objects
  Shape shape;
  int maxPointValue =
      shape.maxPoints; // Variable used as parameter to debugmenu and to update
                       // points on screen(runtime)
  bool changeMaxPoint = false; // Variable used to control the spring updation
  Spring spring;
  SpringSystem springSystem;

  shape.Init(window); // Generate initial points
  // springSystem.InitPerVertex(shape, spring);    // Connect next points with
  // springs (Simulate Rope) springSystem.InitCircular(shape, spring);
  springSystem.InitAll(shape, spring);
  // Main loop
  while (window.isOpen()) {
    // Event handling
    while (const std::optional event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    sf::Time delta = clock.restart();
    ImGui::SFML::Update(window, delta);
    float dt = delta.asSeconds();

    Input::Mouse::Drag(shape.points, window); // Handle dragging
    // Updates the points and spring in screen (runtime)
    shape.Update(window, maxPointValue, changeMaxPoint);
    if (changeMaxPoint) {
      springSystem.UpdateAll(shape, spring);
      changeMaxPoint = false;
    }
    //
    shape.Setup(window, dt); // Physics integration and collision
    springSystem.Setup(dt);  // Apply spring physics
    std::cout << "shape:" << shape.points.size()
              << " spring:" << springSystem.springs.size() << std::endl;
    window.clear(sf::Color::Black);

    Editor::DebugMenu::Draw(springSystem, maxPointValue); // Draw debug UI
    ImGui::End();

    grid.Initialize(window);
    shape.Draw(window);
    springSystem.Draw(window);

    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown(); // Clean up ImGui
  return 0;
}
