#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Points
{
	int mass;
	sf::Vector2f velocity;
	sf::Vector2f position;

};

struct Physics
{
	std::vector<Points> points;
	sf::Vector2f gravity;

	void Update(float dt);

};