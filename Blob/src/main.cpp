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
		gameWindow.WINDOW_TITLE);
	ImGui::SFML::Init(window);

	window.setFramerateLimit(gameWindow.FRAME_RATE);

	// ─── Global Setup ────────────────────────────────────────────────
	Random random;
	sf::Clock clock;

	Shape shape;
	shape.Initialize(window);
	float springRestLength = 100.0f;
	float springConstant = 60.0f;
	std::vector<Spring> springs;
	for (size_t i = 0; i < shape.points.size(); ++i) {
		for (size_t j = i + 1; j < shape.points.size(); ++j) {

			springs.emplace_back(&shape.points[i], &shape.points[j], springRestLength,
				springConstant); // stiffness
		}
	}

	for (auto& point : shape.points) {
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

		for (auto& point : shape.points) {
			PhysicsEngine::Verlet::Apply(point, dt);
			PhysicsEngine::Collision::ResolveWindow(point, window);
		}

		for (size_t i = 0; i < shape.points.size(); ++i) {
			for (size_t j = i + 1; j < shape.points.size(); ++j) {
				PhysicsEngine::Collision::ResolveCircle(shape.points[i],
					shape.points[j]);
			}
		}

		for (auto& spring : springs) {
			PhysicsEngine::Spring::ApplyForce(*spring.a, *spring.b, spring.restLength,
				spring.springConstant, dt);
		}

		// ─── Render ─────────────────────────────────────────────────

		window.clear(sf::Color::Black);

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(250, window.getSize().y), ImGuiCond_Always); // fixed width, full height

		ImGui::Begin("DebugMenu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		Editor::DrawDebugMenu(springs);
		ImGui::End();

		shape.Draw(window);

		for (const auto& line : PhysicsEngine::Spring::linesToDraw) {
			sf::Vertex vertices[2] = { {line.first, sf::Color::White},
									  {line.second, sf::Color::White} };

			window.draw(vertices, 2, sf::PrimitiveType::Lines);
		}

		PhysicsEngine::Spring::linesToDraw.clear();
		ImGui::SFML::Render(window);
		window.display();
	}

	return 0;
};
