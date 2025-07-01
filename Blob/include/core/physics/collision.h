#pragma once
#include <SFML/Graphics.hpp>
#include "../gameobjects/point.h"

namespace PhysicsEngine {

	namespace Collision {

		void ResolveWindow(Point& point, const sf::RenderWindow& window);
		void ResolveCircle(Point& a, Point& b);
	}

}

