#include "../../include/core/input.h"

void Input::MouseDrag(Point &point) {
  bool isPressed = false;
  sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition());
  sf::Vector2f toMousePos = mousePos - point.position;
  float dotVector = toMousePos.x * toMousePos.x + toMousePos.y * toMousePos.y;
  isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

  if (isPressed && (dotVector <= point.radius * point.radius)) {
    point.position = mousePos;
  }
}
