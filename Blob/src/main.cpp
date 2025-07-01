#include "../external/Imgui-SFML/include/imgui-SFML.h"
#include "../external/Imgui/include/imgui.h"
#include "../include/core/config.h"
#include "../include/core/gameobjects/shape.h"
#include "../include/core/gameobjects/spring.h"
#include "../include/core/input.h"
#include "../include/core/physics/physics.h"
#include "../include/core/random.h"
#include "../include/editor/debugmenu.h"

int main() {
    // ─── Window & Settings ───────────────────────────────────────────
    GameWindow gameWindow;
    sf::ContextSettings settings;
    settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

    sf::RenderWindow window(
        sf::VideoMode({ gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT }),
        gameWindow.WINDOW_TITLE,
        sf::Style::Default
    );
    ImGui::SFML::Init(window);
    window.setFramerateLimit(gameWindow.FRAME_RATE);

    // ─── Global Setup ────────────────────────────────────────────────
    const int cellSize = 30;
    const int cols = gameWindow.WINDOW_WIDTH / cellSize + 1;
    const int rows = gameWindow.WINDOW_HEIGHT / cellSize + 1;

    Random random;
    sf::Clock clock;

    Shape shape;
    shape.Initialize(window);
    float springRestLength = 100.0f;
    float springConstant = 60.0f;

    std::vector<Spring> springs;
    for (size_t i = 0; i < shape.points.size(); ++i) {
        for (size_t j = i + 1; j < shape.points.size(); ++j) {
            springs.emplace_back(&shape.points[i], &shape.points[j], springRestLength, springConstant);
        }
    }
    
    // rope simulation
   /* std::vector<Spring> springs;
    for (size_t i = 0; i + 1 < shape.points.size(); ++i) {
        springs.emplace_back(&shape.points[i], &shape.points[i + 1], springRestLength, springConstant);

    }*/

    for (auto& point : shape.points) {
        point.color = sf::Color::White;
    }

    // ─── Main Loop ───────────────────────────────────────────────────
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // ─── Update Logic ─────────────────────────────────────────────
        sf::Time delta = clock.restart();
        ImGui::SFML::Update(window, delta);
        float dt = delta.asSeconds();

        Input::Mouse::Drag(shape.points, window);

        for (auto& point : shape.points) {
            PhysicsEngine::Verlet::Apply(point, dt);
            PhysicsEngine::Collision::ResolveWindow(point, window);
        }

        if (Editor::activeCircleCollide) {
            for (size_t i = 0; i < shape.points.size(); ++i) {
                for (size_t j = i + 1; j < shape.points.size(); ++j) {
                    PhysicsEngine::Collision::ResolveCircle(shape.points[i], shape.points[j]);
                }
            }
        }

        for (auto& spring : springs) {
            PhysicsEngine::Spring::ApplyForce(*spring.a, *spring.b, spring.restLength,
                spring.springConstant, dt);
        }

        // ─── Render ───────────────────────────────────────────────────
        window.clear(sf::Color::Black);

        // UI
        Editor::DrawDebugMenu(springs);
        ImGui::End();

        // Grid

        sf::Color lightGray = sf::Color(80, 80, 80);

        for (int y = 0; y <= rows + 1; ++y) {
            sf::Vertex line[2];
            line[0].position = sf::Vector2f(0.f, y * cellSize);
            line[1].position = sf::Vector2f(cols * cellSize, y * cellSize);

            line[0].color = lightGray;
            line[1].color = lightGray;

            window.draw(line, 2, sf::PrimitiveType::Lines);
        }

        for (int x = 0; x <= cols; ++x) {
            sf::Vertex line[2];
            line[0].position = sf::Vector2f(x * cellSize, 0.f);
            line[1].position = sf::Vector2f(x * cellSize, rows * cellSize);

            line[0].color = lightGray;
            line[1].color = lightGray;

            window.draw(line, 2, sf::PrimitiveType::Lines);
        }

        // Shapes
        shape.Draw(window);

        // Springs
        for (const auto& line : PhysicsEngine::Spring::linesToDraw) {
            sf::Vertex vertices[2] = {
                sf::Vertex{line.first, sf::Color::White},
                sf::Vertex{line.second, sf::Color::White}
            };
            window.draw(vertices, 2, sf::PrimitiveType::Lines);
        }

        PhysicsEngine::Spring::linesToDraw.clear();

        // Render UI and final buffer swap
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
