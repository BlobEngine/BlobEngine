#include "../../../include/core/physics/physics.h"
#include <cmath>
#include <algorithm>

void PhysicsEngine::Verlet::ApplyVerlet(Point& p, float dt) {
    sf::Vector2f force = gravity * static_cast<float>(p.mass);
    p.velocity += force * dt;
    p.position += p.velocity * dt;

    if (p.velocity.x > 0)
        p.velocity.x = std::max(0.0f, p.velocity.x - damping * dt);
    if (p.velocity.y > 0)
        p.velocity.y = std::max(0.0f, p.velocity.y - damping * dt);
}

void PhysicsEngine::Collision::ResolveWindowCollision(Point& point, const sf::RenderWindow& window) {
    if (point.position.x - point.radius < 0 || point.position.x + point.radius > window.getSize().x) {
        point.position.x = std::clamp(point.position.x, point.radius, window.getSize().x - point.radius);
        point.velocity.x = -point.velocity.x;
    }

    if (point.position.y - point.radius < 0 || point.position.y + point.radius > window.getSize().y) {
        point.position.y = std::clamp(point.position.y, point.radius, window.getSize().y - point.radius);
        point.velocity.y = -point.velocity.y;
    }
}

void PhysicsEngine::Collision::ResolveCircleCollision(Point& a, Point& b) {
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

        float overlap = 0.5f * (totalRadius - distance);
        sf::Vector2f normal(dx / distance, dy / distance);
        sf::Vector2f displacement = normal * overlap;

        a.position -= displacement;
        b.position += displacement;
    }
}
