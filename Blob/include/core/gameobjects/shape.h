#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Points {
  float radius = 10;

  int mass = 5;
  sf::Vector2f velocity;
  sf::Vector2f position;
};

struct Shape {
  std::vector<Points> points;
  sf::Vector2f gravity;

  void Update(float dt);
  void WindowCollision(sf::RenderWindow& window, Points& points);
};
