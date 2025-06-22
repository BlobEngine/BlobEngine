#include <random>
#include "../../include/core/random.h"
#include "../../include/core/config.h"

Random::Random()
	: gen(std::random_device{}()),
	distColor(0, 255)
{
	RandomValue rv;
	distVelocityX = std::uniform_real_distribution<float>(rv.MIN_VELOCITY, rv.MAX_VELOCITY);
	distVelocityY = std::uniform_real_distribution<float>(rv.MIN_VELOCITY, rv.MAX_VELOCITY);
	distX = std::uniform_real_distribution<float>(0.f, 1.f);
	distY = std::uniform_real_distribution<float>(0.f, 1.f);
}

sf::Vector2f Random::setPosition(const sf::RenderWindow& window) {
	RandomValue rv;
	float maxX = window.getSize().x - rv.MIN_POSITION;
	float maxY = window.getSize().y - rv.MIN_POSITION;
	distX.param(std::uniform_real_distribution<float>::param_type(0.f, maxX));
	distY.param(std::uniform_real_distribution<float>::param_type(0.f, maxY));
	return sf::Vector2f{ distX(gen), distY(gen) };
}

sf::Vector2f Random::setVelocity() {
	return sf::Vector2f{ distVelocityX(gen), distVelocityY(gen) };
}

sf::Color Random::setColor() {
	return sf::Color(
		static_cast<uint8_t>(distColor(gen)),
		static_cast<uint8_t>(distColor(gen)),
		static_cast<uint8_t>(distColor(gen))
	);
}
