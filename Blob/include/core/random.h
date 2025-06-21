#pragma once
#include <SFML/Graphics.hpp>

namespace shape {

	struct Random {
		sf::Vector2f setPosition(const sf::RenderWindow& window);
		sf::Vector2f setVelocity();
		sf::Color setColor();
	};

}
