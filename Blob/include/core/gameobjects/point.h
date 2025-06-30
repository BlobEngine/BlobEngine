#pragma once
#include <SFML/Graphics.hpp>

struct Point {

    static float mass;
    sf::Vector2f velocity;
    sf::Vector2f position;

    // Extra
    sf::Color color;
    static float radius;
    static float restitution;

};