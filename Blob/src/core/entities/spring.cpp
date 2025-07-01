#include "../../../include/core/entities/spring.h"
#include "../../../include/core/physics/springforce.h"

void SpringSystem::InitDefault(Shape& shape, Spring& spring) {

	for (size_t i = 0; i < shape.points.size(); ++i) {
		for (size_t j = i + 1; j < shape.points.size(); ++j) {
			springs.push_back({ &shape.points[i], &shape.points[j], spring.restLength, spring.springConstant });
		}
	}
}

void SpringSystem::Setup(float dt) {
	for (auto& spring : springs) {
		PhysicsEngine::Spring::ApplyForce(*spring.a, *spring.b, spring.restLength, spring.springConstant, dt);
	}
}

void SpringSystem::Draw(sf::RenderWindow& window) {
	// Springs
	for (const auto& line : PhysicsEngine::Spring::linesToDraw) {
		sf::Vertex vertices[2] = {
			sf::Vertex{line.first, sf::Color::White},
			sf::Vertex{line.second, sf::Color::White}
		};
		window.draw(vertices, 2, sf::PrimitiveType::Lines);
	}

	PhysicsEngine::Spring::linesToDraw.clear();
}

void SpringSystem::InitRope(Shape &shape, Spring& spring) {
	// Rope Simulation
	for (size_t i = 0; i + 1 < shape.points.size(); ++i) {
		springs.push_back({ &shape.points[i], &shape.points[i + 1], spring.restLength, spring.springConstant });

	}
}