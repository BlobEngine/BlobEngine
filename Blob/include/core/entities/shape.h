#pragma once
#include "../entities/point.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct Shape {

  static int maxPoints;
  std::vector<Point> points;

  void Init(sf::RenderWindow &window); // Setup points with random values
  void Update(sf::RenderWindow &window, int &maxpointvalue,
              bool &changeMaxPoint);
  void Setup(sf::RenderWindow &window, float dt);
  void Draw(sf::RenderWindow &window); // Render each point on screen
};
