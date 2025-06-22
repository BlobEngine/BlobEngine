#include "../../include/core/input.h"

void Input::MouseDrag(std::vector<Point>& points, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (isPressed) {
        if (selectedPoint == nullptr) {
            for (auto& point : points) {
                sf::Vector2f toMouse = mousePos - point.position;
                float distSquared = toMouse.x * toMouse.x + toMouse.y * toMouse.y;
                if (distSquared <= point.radius * point.radius) {
                    selectedPoint = &point;
                    prevMousePos = mousePos;  // Start tracking
                    break;
                }
            }
        }

        if (selectedPoint) {
            // Apply dragging
            selectedPoint->position = mousePos;
        }

    }
    else {
        // Release: apply velocity from mouse drag
        if (selectedPoint) {
            selectedPoint->velocity = (mousePos - prevMousePos) * throwMultiplier;  // Momentum = displacement
        }

        selectedPoint = nullptr;
    }

    // Update last position for next frame (only if dragging)
    if (selectedPoint) {
        prevMousePos = mousePos;
    }
}

