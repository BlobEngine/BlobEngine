#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Points {

  float radius = 10;

  int mass = 5;
  sf::Vector2f velocity;
  sf::Vector2f position;

  float restitution = 1.0f;
  float damping = 20.0f;
};

struct Shape {
  std::vector<Points> points;
  sf::Vector2f gravity;

  void Move(float dt);
  void WindowCollision(sf::RenderWindow& window, Points& points);
  void CircleCollision(Points& pointA, Points& pointB);
};
