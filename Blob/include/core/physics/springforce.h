#pragma once
#include <SFML/Graphics.hpp>
#include "../gameobjects/point.h"

namespace PhysicsEngine {

	namespace Spring {
		inline float damping = 10.0f;
		inline std::vector<std::pair<sf::Vector2f, sf::Vector2f>> linesToDraw;

		void ApplyForce(Point& a, Point& b, float restLength, float springConstant, float dt);
	}

}
