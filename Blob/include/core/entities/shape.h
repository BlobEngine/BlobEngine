#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../entities/point.h"

struct Shape {

    int maxPoints = 10;
    std::vector<Point> points;

    void Initialize(sf::RenderWindow& window);    // Setup points with random values
    void Setup(sf::RenderWindow& window, float dt);
    void Draw(sf::RenderWindow& window);          // Render each point on screen

};
