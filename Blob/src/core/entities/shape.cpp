#include "../../../include/core/entities/shape.h"
#include "../../../include/core/physics/collision.h"
#include "../../../include/core/physics/verlet.h"
#include "../../../include/core/system/random.h"
#include "../../../include/editor/debugmenu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>

int Shape::maxPoints = 8;

// Initialize maxPoints with random position and random velocity
void Shape::Init(sf::RenderWindow &window) {
  Random random;
  Point temp;
  for (int i = 0; i < maxPoints; ++i) {
    temp.position = random.setPosition(window);
    temp.velocity = random.setVelocity();
    points.push_back(temp);
  }
}
// Updates the number of points in screen (runtime)
void Shape::Update(sf::RenderWindow &window, int &maxpointvalue,
                   bool &changeMaxPoint) {
  Random random;
  Point temp;
  int count = Shape::maxPoints;
  while (maxpointvalue != count) {
    if (maxpointvalue > count) {
      temp.position = random.setPosition(window);
      temp.velocity = random.setVelocity();
      points.push_back(temp);
      count++;
    }
    if (maxpointvalue < count) {
      points.pop_back();
      count--;
    }
    if (maxpointvalue == count) {
      changeMaxPoint = true;
    }
  }
}

void Shape::Setup(sf::RenderWindow &window, float dt) {

  // Apply Verlet & Window Collision
  for (auto &point : points) {
    PhysicsEngine::Verlet::Apply(point, dt);
    PhysicsEngine::Collision::ResolveWindow(point, window);
  }

  // Apply Circle Collision
  if (Editor::DebugMenu::activeCircleCollide) {
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = i + 1; j < points.size(); ++j) {
        PhysicsEngine::Collision::ResolveCircle(points[i], points[j]);
      }
    }
  }
}

// Draw points as circleShape
void Shape::Draw(sf::RenderWindow &window) {

  Random random;
  for (auto &p : points) {
    sf::CircleShape circle(p.radius);
    circle.setOrigin(sf::Vector2f{p.radius, p.radius});
    circle.setFillColor(p.color);
    circle.setPosition(p.position);
    window.draw(circle);
  }
}
