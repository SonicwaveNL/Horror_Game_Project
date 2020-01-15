#include "../Headers/keyboardMouse.hpp"

bool KeyboardMouse::checkInput(sf::Keyboard::Key& input) {
  if (sf::Keyboard::isKeyPressed(input)) {
    return true;
  }
  return false;
}

sf::Vector2f KeyboardMouse::getMousePos(sf::RenderWindow& window) {
  return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}