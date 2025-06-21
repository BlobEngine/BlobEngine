#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Point {
    int mass = 5;                         // Mass of the point, affects physics
    float radius = 20.0f;                 // Radius used for drawing and collisions
    float restitution = 1.0f;             // Bounciness (1 = fully elastic)
    float damping = 10.0f;                // Slows down the motion over time
    sf::Vector2f velocity;                // Movement speed and direction
    sf::Vector2f position;                // Current screen position
    sf::Color color;                      // Render color
};

struct Shape {
    int maxPoints = 100;                  // Maximum number of points allowed
    std::vector<Point> points;            // Container for all particles
    sf::Vector2f gravity{ 0.0f, 100.0f }; // Constant downward force

    void Initialize(sf::RenderWindow& window);                      // Setup points with random values
    void Move(float dt);                                            // Update all point physics
    void Draw(sf::RenderWindow& window);                            // Render each point on screen
    void WindowCollision(sf::RenderWindow& window, Point& point);   // Bounce point off window edge
    void CircleCollision(Point& a, Point& b);                       // Resolve point-to-point collision
};
