#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

//struct Shape; // Forward declaration

struct Point {
    int mass = 5;
    float radius = 10.0f;
    float restitution = 1.0f;
    float damping = 20.0f;

    sf::Vector2f velocity;
    sf::Vector2f position;

    sf::Vector2f SetRandom(const sf::RenderWindow& window);
};

struct Shape {
    int maxPoints = 300;
    std::vector<Point> points;
    sf::Vector2f gravity{ 0.0f, 100.0f };

    void Initialize(sf::RenderWindow& window);
    void Move(float dt);
    void Draw(sf::RenderWindow& window);
    void WindowCollision(sf::RenderWindow& window, Point& point);
    void CircleCollision(Point& a, Point& b);
};
