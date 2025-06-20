#include "../../../include/core/gameobjects/shape.h"

void Shape::Update(float dt) {
  for (auto &p : points) {
    sf::Vector2f force = sf::Vector2f{p.mass * gravity.x, p.mass * gravity.y};
    p.velocity += force * dt;
    p.position += p.velocity * dt;
  }
}
