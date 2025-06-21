#include <SFML/Graphics.hpp>
#include "../include/core/random.h"
#include "../include/core/gameobjects/shape.h"

int main() {
	// ─── Window & Settings ─────────────────────────────────────────────
	GameWindow gameWindow;
	sf::ContextSettings settings;
	settings.antiAliasingLevel = gameWindow.ANTI_ALIASING;

	sf::RenderWindow window(
		sf::VideoMode({ gameWindow.WINDOW_WIDTH, gameWindow.WINDOW_HEIGHT }),
		gameWindow.WINDOW_TITLE
	);
	window.setFramerateLimit(gameWindow.FRAME_RATE);

	// ─── Global Setup ─────────────────────────────────────────────────
	shape::Random random;
	sf::Clock clock;

	// ─── Shape Initialization ─────────────────────────────────────────
	Shape shape;
	shape.Initialize(window);

	for (auto& point : shape.points) {
		point.color = random.setColor();
	}

	// ─── Main Loop ────────────────────────────────────────────────────
	while (window.isOpen()) {

		// ─── Handle Events ─────────────────────────────────────────────
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		// ─── Update Logic ──────────────────────────────────────────────
		float dt = clock.restart().asSeconds();
		shape.Move(dt);

		// ─── Collision: Window Edges ──────────────────────────────────
		for (auto& point : shape.points) {
			shape.WindowCollision(window, point);
		}

		// ─── Collision: Circle vs Circle ───────────────────────────────
		for (size_t i = 0; i < shape.points.size(); ++i) {
			for (size_t j = i + 1; j < shape.points.size(); ++j) {
				shape.CircleCollision(shape.points[i], shape.points[j]);
			}
		}

		// ─── Render ────────────────────────────────────────────────────
		window.clear(sf::Color::Black);
		shape.Draw(window);
		window.display();
	}

	return 0;
}
