#pragma once
#include <SFML/Graphics.hpp>
#include <random>

struct Random {
	Random();

	sf::Vector2f setPosition(const sf::RenderWindow& window);  // Generate random position inside window bounds
	sf::Vector2f setVelocity();                                // Generate random velocity vector
	sf::Color setColor();                                      // Generate random color

private:
	std::mt19937 gen;
	std::uniform_int_distribution<int> distColor;
	std::uniform_real_distribution<float> distVelocityX;
	std::uniform_real_distribution<float> distVelocityY;
	std::uniform_real_distribution<float> distX;
	std::uniform_real_distribution<float> distY;
};

