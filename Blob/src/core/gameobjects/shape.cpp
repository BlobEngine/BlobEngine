#include "../../../include/core/gameobjects/shape.h"
#include <cmath>

void Shape::Move(float dt) {
  for (auto &p : points) {
    sf::Vector2f force = sf::Vector2f{p.mass * gravity.x, p.mass * gravity.y};
    p.velocity += force * dt;
    p.position += p.velocity * dt;

    if (p.velocity.x > 0)
    {
        p.velocity.x = std::max(0.0f, p.velocity.x - p.damping * dt);
    }
    if (p.velocity.y > 0)
    {
        p.velocity.y = std::max(0.0f, p.velocity.y - p.damping * dt);
    }
  }
}

void Shape::WindowCollision(sf::RenderWindow& window, Points& points) {

    // x axis
    if (points.position.x - points.radius < 0 || points.position.x + points.radius > window.getSize().x) {
        points.position.x = std::clamp(points.position.x, points.radius, window.getSize().x - points.radius);
        points.velocity.x = -points.velocity.x;
    }

    // y axis
    if (points.position.y - points.radius < 0 || points.position.y + points.radius > window.getSize().y) {
        points.position.y = std::clamp(points.position.y, points.radius, window.getSize().y - points.radius);
        points.velocity.y = -points.velocity.y;
    }
}

void Shape::CircleCollision(Points& a, Points& b) {
    float dx = b.position.x - a.position.x;
    float dy = b.position.y - a.position.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    float totalRadius = a.radius + b.radius;

    if (distance < totalRadius && distance != 0.0f) {
        float angle = std::atan2(dy, dx);

        float v1x = a.velocity.x * std::cos(angle) + a.velocity.y * std::sin(angle);
        float v1y = a.velocity.y * std::cos(angle) - a.velocity.x * std::sin(angle);
        float v2x = b.velocity.x * std::cos(angle) + b.velocity.y * std::sin(angle);
        float v2y = b.velocity.y * std::cos(angle) - b.velocity.x * std::sin(angle);

        float v1PrimeX = (v1x * (a.mass - b.mass) + 2 * b.mass * v2x) * a.restitution / (a.mass + b.mass);
        float v2PrimeX = (v2x * (b.mass - a.mass) + 2 * a.mass * v1x) * b.restitution / (a.mass + b.mass);

        a.velocity.x = v1PrimeX * std::cos(-angle) + v1y * std::sin(-angle);
        a.velocity.y = v1y * std::cos(-angle) - v1PrimeX * std::sin(-angle);
        b.velocity.x = v2PrimeX * std::cos(-angle) + v2y * std::sin(-angle);
        b.velocity.y = v2y * std::cos(-angle) - v2PrimeX * std::sin(-angle);

        // Position correction
        float overlap = 0.5f * (totalRadius - distance);
        sf::Vector2f normal = sf::Vector2f(dx / distance, dy / distance);
        sf::Vector2f displacement = normal * overlap;

        a.position -= displacement;
        b.position += displacement;
    }

}
