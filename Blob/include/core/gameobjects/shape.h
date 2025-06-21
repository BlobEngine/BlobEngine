#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Point {
    int mass = 5;
    float radius = 20.0f;
    float restitution = 1.0f;
    float damping = 10.0f;

    sf::Vector2f velocity;
    sf::Vector2f position;

    sf::Color color;
};

struct Shape {
    int maxPoints = 100;
    std::vector<Point> points;
    sf::Vector2f gravity{ 0.0f, 100.0f };

    void Initialize(sf::RenderWindow& window);
    void Move(float dt);
    void Draw(sf::RenderWindow& window);
    void WindowCollision(sf::RenderWindow& window, Point& point);
    void CircleCollision(Point& a, Point& b);
};
