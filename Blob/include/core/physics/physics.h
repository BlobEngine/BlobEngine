#pragma once
#include <SFML/Graphics.hpp>
#include "../gameobjects/point.h"

namespace PhysicsEngine {

    namespace Verlet {

       inline float gravityX = 0.0f;
       inline float gravityY = 0.0f;
       inline float damping = 0.0f;
       inline sf::Vector2f gravity{ gravityX, gravityY };

       void Apply(Point& p, float dt);

    };

    namespace Collision {

        void ResolveWindow(Point& point, const sf::RenderWindow& window);
        void ResolveCircle(Point& a, Point& b);
    };

    namespace Spring {

       inline float springDamping = 10.0f;
       inline std::vector<std::pair<sf::Vector2f, sf::Vector2f>> springLinesToDraw;

        void ApplyForce(Point& a, Point& b, float restLength, float springConstant, float dt);
    };

}