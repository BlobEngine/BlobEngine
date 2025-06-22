#pragma once
#include <SFML/Graphics.hpp>

struct Point {

    int mass = 5;
    sf::Vector2f velocity;
    sf::Vector2f position;

    // Extra
    sf::Color color;
    float radius = 20.0f;
    float restitution = 0.85f;

};