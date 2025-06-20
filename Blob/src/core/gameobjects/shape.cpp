#include "../../../include/core/gameobjects/shape.h"

void Shape::Update(float dt) {
  for (auto &p : points) {
    sf::Vector2f force = sf::Vector2f{p.mass * gravity.x, p.mass * gravity.y};
    p.velocity += force * dt;
    p.position += p.velocity * dt;
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
