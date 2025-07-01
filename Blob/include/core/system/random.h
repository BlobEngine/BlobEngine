#pragma once
#include <SFML/Graphics.hpp>
#include <random>

struct Random {
	Random();

	sf::Vector2f setPosition(const sf::RenderWindow& window);  
	sf::Vector2f setVelocity();                               
	sf::Color setColor();                                     

private:
	std::mt19937 gen;
	std::uniform_int_distribution<int> distColor;
	std::uniform_real_distribution<float> distVelocityX;
	std::uniform_real_distribution<float> distVelocityY;
	std::uniform_real_distribution<float> distX;
	std::uniform_real_distribution<float> distY;
};

