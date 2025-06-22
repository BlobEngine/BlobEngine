#include "SFML/Graphics.hpp"
#include "gameobjects/point.h"

struct Input {
  Point* selectedPoint = nullptr;
  sf::Vector2f prevMousePos{ 0.f, 0.f };
  float throwMultiplier = 15.0f;

  void MouseDrag(std::vector<Point>& points, const sf::RenderWindow& window);
};
