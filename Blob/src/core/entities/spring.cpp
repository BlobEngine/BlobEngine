#include "../../../include/core/entities/spring.h"
#include "../../../include/core/physics/springforce.h"
#include <cstddef>
#include <iostream>

void SpringSystem::InitAll(Shape& shape, Spring& spring) {

	for (size_t i = 0; i < shape.points.size(); ++i) {
		for (size_t j = i + 1; j < shape.points.size(); ++j) {
			springs.push_back({ &shape.points[i], &shape.points[j], spring.restLength,
							   spring.springConstant });
		}
	}
}
// Updates the spring in runtime
void SpringSystem::UpdateAll(Shape& shape, Spring& spring) {

	ClearSpring();
	shape.maxPoints = shape.points.size();
	InitAll(shape, spring);
}

void SpringSystem::Setup(float dt) {
	for (auto& spring : springs) {
		PhysicsEngine::Spring::ApplyForce(*spring.a, *spring.b, spring.restLength,
			spring.springConstant, dt);
	}
}

void SpringSystem::Draw(sf::RenderWindow& window) {
	// Springs
	for (const auto& line : PhysicsEngine::Spring::linesToDraw) {
		sf::Vertex vertices[2] = { sf::Vertex{line.first, sf::Color::White},
								  sf::Vertex{line.second, sf::Color::White} };
		window.draw(vertices, 2, sf::PrimitiveType::Lines);
	}

	PhysicsEngine::Spring::linesToDraw.clear();
}

// EXTRAS
void SpringSystem::InitPerMesh(Shape& shape, Spring& spring) {
	for (size_t i = 0; i + 1 < shape.points.size(); ++i) {
		springs.push_back({ &shape.points[i], &shape.points[i + 1],
						   spring.restLength, spring.springConstant });
		if (i + 2 < shape.points.size())
			springs.push_back({ &shape.points[i], &shape.points[i + 2],
							   spring.restLength, spring.springConstant });
	}
}

void SpringSystem::UpdatePerMesh(Shape& shape, Spring& spring) {
	
	ClearSpring();
	shape.maxPoints = shape.points.size();
	InitPerMesh(shape, spring);

}

void SpringSystem::InitPerVertex(Shape& shape, Spring& spring) {
	// Rope Simulation
	for (size_t i = 0; i + 1 < shape.points.size(); ++i) {
		springs.push_back({ &shape.points[i], &shape.points[i + 1],
						   spring.restLength, spring.springConstant });
	}
}

void SpringSystem::UpdatePerVertex(Shape& shape, Spring& spring) {

	ClearSpring();
	shape.maxPoints = shape.points.size();
	InitPerVertex(shape, spring);

}

void SpringSystem::InitRadialCenter(Shape& shape, Spring& spring) {

	if (shape.points.empty())
		return;
	Point* center = &shape.points[0]; // assume first is center
	for (size_t i = 1; i < shape.points.size(); ++i) {
		springs.push_back(
			{ center, &shape.points[i], spring.restLength, spring.springConstant });
	}
}

void SpringSystem::UpdateRadialCenter(Shape& shape, Spring& spring) {

	ClearSpring();
	shape.maxPoints = shape.points.size();
	InitRadialCenter(shape, spring);

}

void SpringSystem::InitCircularCenter(Shape& shape, Spring& spring) {
	if (shape.points.size() < 3)
		return;
	Point* center = &shape.points[0];

	// Ring + spokes
	for (size_t i = 1; i < shape.points.size(); ++i) {
		springs.push_back(
			{ center, &shape.points[i], spring.restLength, spring.springConstant });
		size_t next = (i + 1 < shape.points.size()) ? i + 1 : 1;
		springs.push_back({ &shape.points[i], &shape.points[next], spring.restLength,
						   spring.springConstant });
	}
}

void SpringSystem::UpdateCircularCenter(Shape& shape, Spring& spring) {

	ClearSpring();
	shape.maxPoints = shape.points.size();
	InitCircularCenter(shape, spring);
}

void SpringSystem::ClearSpring() {

	size_t springSize = springs.size();
	for (size_t i = 0; i < springSize; ++i) {
		std::cout << "springshape:" << springSize << std::endl;
		springs.pop_back();
	}
}
