#include <algorithm>
#include "../../../include/core/gameobjects/shape.h"
#include "../../../include/core/random.h"
#include "../../../include/core/physics/physics.h"
#include "../../../include/editor/debugmenu.h"

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


void Shape::Setup(sf::RenderWindow& window, float dt) {

    // Apply Verlet & Window Collision
    for (auto& point : points) {
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

