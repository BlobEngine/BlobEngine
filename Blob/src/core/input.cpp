#include "../../include/core/input.h"

void Input::Mouse::Drag(std::vector<Point>& points, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    Point* hoveredPoint = nullptr;

    // First, handle hover color (even without click)
    for (auto& point : points) {
        sf::Vector2f toMouse = mousePos - point.position;
        float distSquared = toMouse.x * toMouse.x + toMouse.y * toMouse.y;

        if (distSquared <= point.radius * point.radius) {
            point.color = sf::Color::Yellow; // Hover color
            hoveredPoint = &point;
        }
        else {
            point.color = sf::Color::White; // Default color
        }
    }

    // Handle drag logic
    if (isPressed) {
        if (selectedPoint == nullptr && hoveredPoint) {
            selectedPoint = hoveredPoint;
            prevMousePos = mousePos;
        }

        if (selectedPoint) {
            selectedPoint->position = mousePos;
            selectedPoint->color = sf::Color::Green; // Dragging color
        }
    }
    else {
        if (selectedPoint) {
            selectedPoint->velocity = (mousePos - prevMousePos) * throwMultiplier;
            selectedPoint = nullptr;
        }
    }

    if (selectedPoint) {
        prevMousePos = mousePos;
    }
}


