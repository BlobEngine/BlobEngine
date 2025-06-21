#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "../config.h"

struct Point {

    physics::DefaultValue value;

    sf::Vector2f velocity;
    sf::Vector2f position;              
    sf::Color color;

    int mass = value.MASS;                      
    float radius = value.RADIUS;               
    float restitution = value.RESTITUTION;           
    float damping = value.DAMPING;           

};

struct Shape {

    physics::DefaultValue value;

    int maxPoints = value.MAXPOINTS;                  
    std::vector<Point> points;                                     
    sf::Vector2f gravity{ value.GRAVITY_X, value.GRAVITY_Y }; 

    void Initialize(sf::RenderWindow& window);                      // Setup points with random values
    void Move(float dt);                                            // Update all point physics
    void Draw(sf::RenderWindow& window);                            // Render each point on screen
    void WindowCollision(sf::RenderWindow& window, Point& point);   // Bounce point off window edge
    void CircleCollision(Point& a, Point& b);                       // Resolve point-to-point collision
};
