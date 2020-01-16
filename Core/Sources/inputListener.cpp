#include <../Headers/inputHandler.hpp>

bool InputListener::checkInput(sf::Keyboard::Key & input) { return false; };

bool InputListener::checkInput(sf::Joystick::Axis & input) { return false; };

sf::Vector2f InputListener::getMousePos(sf::RenderWindow & window) {
    return sf::Vector2f(0.0f, 0.0f);
};