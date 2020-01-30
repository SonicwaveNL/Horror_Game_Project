#include <../Headers/keyboardMouse.hpp>
bool KeyboardMouse::checkInput(sf::Keyboard::Key & input) {
    return sf::Keyboard::isKeyPressed(input);
}

sf::Vector2f KeyboardMouse::getMousePos(sf::RenderWindow & window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}