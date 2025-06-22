#include <algorithm>
#include "../../../include/core/gameobjects/shape.h"
#include "../../../include/core/random.h"

// Initialize maxPoints with random position and random velocity
void Shape::Initialize(sf::RenderWindow& window) {
    Random random;
    Point temp;
    for (int i = 0; i < maxPoints; ++i) {
        temp.position = random.setPosition(window);
        temp.velocity = random.setVelocity();
        points.push_back(temp);
    }
}

// Draw points as circleShape
void Shape::Draw(sf::RenderWindow& window) {

    Random random;
    for (auto& p : points)
    {
        sf::CircleShape circle(p.radius);
        circle.setOrigin(sf::Vector2f{ p.radius, p.radius });
        circle.setFillColor(p.color);
        circle.setPosition(p.position);
        window.draw(circle);
    }
}

