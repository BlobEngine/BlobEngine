#include "../../../include/core/physics/verlet.h"
#include <cmath>
#include <algorithm>

void PhysicsEngine::Verlet::Apply(Point& p, float dt) {
    sf::Vector2f force = gravity * static_cast<float>(p.mass);
    p.velocity += force * dt;
    p.position += p.velocity * dt;

    if (p.velocity.x > 0)
        p.velocity.x = std::max(0.0f, p.velocity.x - damping * dt);
    if (p.velocity.y > 0)
        p.velocity.y = std::max(0.0f, p.velocity.y - damping * dt);
}