#pragma once
#include <SFML/Graphics.hpp>
#include "../gameobjects/point.h"

namespace PhysicsEngine {

    // ─── Verlet Integration ─────────────────────────────────────────
    namespace Verlet {
        inline sf::Vector2f gravity = { 0.0f, 0.0f }; 
        inline float damping = 0.0f;                  

        void Apply(Point& p, float dt);
    }

    // ─── Collision Handling ─────────────────────────────────────────
    namespace Collision {
        void ResolveWindow(Point& point, const sf::RenderWindow& window);
        void ResolveCircle(Point& a, Point& b);
    }

    // ─── Spring Force Physics ───────────────────────────────────────
    namespace Spring {
        inline float damping = 10.0f;
        inline std::vector<std::pair<sf::Vector2f, sf::Vector2f>> linesToDraw;

        void ApplyForce(Point& a, Point& b, float restLength, float springConstant, float dt);
    }

} // namespace PhysicsEngine
