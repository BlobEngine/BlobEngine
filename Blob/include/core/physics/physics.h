#pragma once
#include <SFML/Graphics.hpp>
#include "../gameobjects/point.h"

namespace PhysicsEngine {

    struct Verlet {

        float gravityX = 0.0f;
        float gravityY = 100.0f;
        float damping = 10.0f;
        sf::Vector2f gravity{ gravityX, gravityY };

        void ApplyVerlet(Point& p, float dt);

    };

    struct Collision {

        void ResolveWindowCollision(Point& point, const sf::RenderWindow& window);
        void ResolveCircleCollision(Point& a, Point& b);
    };

    

}