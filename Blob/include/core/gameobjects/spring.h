#pragma once
#include "../../core/gameobjects/point.h"

struct Spring {
    Point* a;
    Point* b;
    float restLength;
    float springConstant;

    Spring(Point* a_, Point* b_, float k)
        : a(a_), b(b_), springConstant(k) {
        
        sf::Vector2f delta = b->position - a->position;
        restLength = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    }
};