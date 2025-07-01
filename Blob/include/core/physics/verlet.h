#pragma once
#include <SFML/Graphics.hpp>
#include "../gameobjects/point.h"

namespace PhysicsEngine {

	namespace Verlet {

		inline sf::Vector2f gravity = { 0.0f, 0.0f };
		inline float damping = 0.0f;

		void Apply(Point& p, float dt);
	}
}