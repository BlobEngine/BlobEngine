#include <SFML/Graphics.hpp>"
#include "../entities/point.h"

namespace Input {

	namespace Mouse {

		inline Point* selectedPoint = nullptr;
		inline sf::Vector2f prevMousePos{ 0.f, 0.f };
		inline float throwMultiplier = 15.0f;

		void Drag(std::vector<Point>& points, const sf::RenderWindow& window);
  }
};
