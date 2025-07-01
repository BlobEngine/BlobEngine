#include "../external/Imgui-SFML/include/imgui-SFML.h"
#include "../external/Imgui/include/imgui.h"

#include "../include/core/config.h"
#include "../include/core/gameobjects/shape.h"
#include "../include/core/gameobjects/spring.h"
#include "../include/core/input.h"
#include "../include/core/random.h"

#include "../include/editor/debugmenu.h"
#include "../include/editor/grid.h"

int main() {
    // ─── Window & ImGui Initialization ───────────────────────────────
    GameWindow gameWindow;
    sf::ContextSettings settings;
    settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

    sf::RenderWindow window(
        sf::VideoMode({ gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT }),
        gameWindow.WINDOW_TITLE,
        sf::Style::Default
    );
    window.setFramerateLimit(gameWindow.FRAME_RATE);
    ImGui::SFML::Init(window);

    // ─── Core Systems Initialization ─────────────────────────────────
    Random random;         // Random number generator for point placement, etc.
    sf::Clock clock;       // For frame delta time
    Grid grid;             // Grid overlay

    Shape shape;           // The dynamic shape made of points
    Spring spring;         // Temporary spring (not directly used here)
    SpringSystem springSystem;  // Handles spring connection and forces

    shape.Initialize(window);                     // Create points
    springSystem.InitDefault(shape, spring);      // Connect springs between points

    // ─── Simulation Main Loop ────────────────────────────────────────
    while (window.isOpen()) {
        // Handle window & ImGui events
        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // ─── Time Step Update ───────────────────────────────────────
        sf::Time delta = clock.restart();
        ImGui::SFML::Update(window, delta);
        float dt = delta.asSeconds();

        // ─── User Input ─────────────────────────────────────────────
        Input::Mouse::Drag(shape.points, window);  // Dragging points with mouse

        // ─── Physics Updates ────────────────────────────────────────
        shape.Setup(window, dt);                   // Verlet integration + collisions
        springSystem.Setup(dt);                    // Apply spring forces

        // ─── Rendering ──────────────────────────────────────────────
        window.clear(sf::Color::Black);            // Clear background

        Editor::DebugMenu::Draw(springSystem);     // Draw ImGui debug panel
        ImGui::End();

        grid.Initialize(window);                   // Draw grid lines
        shape.Draw(window);                        // Draw points
        springSystem.Draw(window);                 // Draw springs

        ImGui::SFML::Render(window);               // Render ImGui UI
        window.display();                          // Swap front/back buffers
    }

    // ─── Shutdown ───────────────────────────────────────────────────
    ImGui::SFML::Shutdown();
    return 0;
}
