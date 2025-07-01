#include <cmath>
#include <algorithm>
#include "../../../include/core/physics/springforce.h"

void PhysicsEngine::Spring::ApplyForce(Point& a, Point& b, float restLength, float springConstant, float dt) {

    sf::Vector2f delta = b.position - a.position;
    float currentLength = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (currentLength == 0.0f) return;

    sf::Vector2f direction = delta / currentLength;
    float displacement = currentLength - restLength;

    // Hooke's Law
    sf::Vector2f springForce = springConstant * displacement * direction;

    // Damping
    sf::Vector2f relativeVelocity = b.velocity - a.velocity;
    float dampingForceMag = relativeVelocity.x * direction.x + relativeVelocity.y * direction.y;
    sf::Vector2f dampingForce = damping * dampingForceMag * direction;

    // Total Force
    sf::Vector2f totalForce = springForce + dampingForce;

    // Apply Force
    sf::Vector2f aAccel = totalForce * (1.0f / a.mass);
    sf::Vector2f bAccel = -totalForce * (1.0f / b.mass);

    a.velocity += aAccel * dt;
    b.velocity += bAccel * dt;

    linesToDraw.emplace_back(a.position, b.position);
}