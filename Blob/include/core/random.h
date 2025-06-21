#pragma once
#include <SFML/Graphics.hpp>

namespace shape {

	struct Random {
		sf::Vector2f setPosition(const sf::RenderWindow& window);  // Generate random position inside window bounds
		sf::Vector2f setVelocity();                                // Generate random velocity vector
		sf::Color setColor();                                      // Generate random color for the point
	};

}
